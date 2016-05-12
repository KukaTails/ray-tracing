#include "geometry/transform.h"

#include <iostream>

namespace leptus {

Matrix4::Matrix4( )
{
  m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0;
  m[0][1] = m[0][2] = m[0][3] = 0.0;
  m[1][0] = m[1][2] = m[1][3] = 0.0;
  m[2][0] = m[2][1] = m[2][3] = 0.0;
  m[3][0] = m[3][1] = m[3][2] = 0.0;
}

Matrix4::Matrix4(Float mat[4][4])
{
  memcpy(m, mat, 16 * sizeof(Float));
}

Matrix4::Matrix4(Float t00, Float t01, Float t02, Float t03,
                 Float t10, Float t11, Float t12, Float t13,
                 Float t20, Float t21, Float t22, Float t23,
                 Float t30, Float t31, Float t32, Float t33)
{
  m[0][0] = t00;
  m[0][1] = t01;
  m[0][2] = t02;
  m[0][3] = t03;
  m[1][0] = t10;
  m[1][1] = t11;
  m[1][2] = t12;
  m[1][3] = t13;
  m[2][0] = t20;
  m[2][1] = t21;
  m[2][2] = t22;
  m[2][3] = t23;
  m[3][0] = t30;
  m[3][1] = t31;
  m[3][2] = t32;
  m[3][3] = t33;
}

bool Matrix4::operator==(const Matrix4& rhs) const
{
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if (m[i][j] != rhs.m[i][j]) return false;
  return true;
}

bool Matrix4::operator!=(const Matrix4& rhs) const
{
  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      if (m[i][j] != rhs.m[i][j]) return true;
  return false;
}

Matrix4 Matrix4::Mul(const Matrix4& lhs, const Matrix4& rhs)
{
  Matrix4 result;

  for (int i = 0; i < 4; ++i)
    for (int j = 0; j < 4; ++j)
      result.m[i][j] = lhs.m[i][0] * rhs.m[0][j] + rhs.m[i][1] * rhs.m[1][j] +
      lhs.m[i][2] * rhs.m[2][j] + lhs.m[i][3] * rhs.m[3][j];
  return result;
}

Matrix4 Matrix4::Inverse(const Matrix4& mat)
{
  int indxc[4], indxr[4];
  int ipiv[4] = {0, 0, 0, 0};
  Float minv[4][4];
  memcpy(minv, mat.m, 4 * 4 * sizeof(Float));

  for (int i = 0; i < 4; i++) {
    int irow = 0, icol = 0;
    Float big = 0.f;
    for (int j = 0; j < 4; j++) {
      if (ipiv[j] != 1) {
        for (int k = 0; k < 4; k++) {
          if (ipiv[k] == 0) {
            if (std::abs(minv[j][k]) >= big) {
              big = Float(std::abs(minv[j][k]));
              irow = j;
              icol = k;
            }
          } else if (ipiv[k] > 1)
            std::cout << "Singular matrix in MatrixInvert" << std::endl;
        }
      }
    }
    ++ipiv[icol];
    if (irow != icol) {
      for (int k = 0; k < 4; ++k)
        std::swap(minv[irow][k], minv[icol][k]);
    }
    indxr[i] = irow;
    indxc[i] = icol;
    if (minv[icol][icol] == 0.f)
      std::cout << "Singular matrix in MatrixInvert" << std::endl;

    Float pivinv = 1. / minv[icol][icol];
    minv[icol][icol] = 1.;
    for (int j = 0; j < 4; j++) minv[icol][j] *= pivinv;

    for (int j = 0; j < 4; j++) {
      if (j != icol) {
        Float save = minv[j][icol];
        minv[j][icol] = 0;
        for (int k = 0; k < 4; k++) minv[j][k] -= minv[icol][k] * save;
      }
    }
  }
  for (int j = 3; j >= 0; j--) {
    if (indxr[j] != indxc[j]) {
      for (int k = 0; k < 4; k++)
        std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
    }
  }
  return Matrix4(minv);
}

inline Float Radians(Float theta)
{
  return theta / 360.0 * 2 * M_PI;
}

Transform::Transform(const Matrix4& mat, const Matrix4& inv_mat)
  : mat_(mat), inv_mat_(inv_mat)
{ }

Transform Translate(Float x, Float y, Float z)
{
  Matrix4 mat(1, 0, 0, x, 0, 1, 0, y, 0, 0, 1, z, 0, 0, 0, 1);
  Matrix4 inv_mat(1, 0, 0, -x, 0, 1, 0, -y, 0, 0, 1, -z, 0, 0, 0, 1);
  return Transform(mat, inv_mat);
}

Transform Scale(Float x, Float y, Float z)
{
  Matrix4 mat(x, 0, 0, 0, 0, y, 0, 0, 0, 0, z, 0, 0, 0, 0, 1);
  Matrix4 inv_mat(1 / x, 0, 0, 0, 0, 1 / y, 0, 0, 0, 0, 1 / z, 0, 0, 0, 0, 1);
  return Transform(mat, inv_mat);
}

Transform RotateX(Float theta)
{
  Float sin_theta = std::sin(Radians(theta));
  Float cos_theta = std::cos(Radians(theta));
  Matrix4 mat(1, 0, 0, 0, 0, cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0, 0, 0, 0, 1);
  Matrix4 inv_mat(1, 0, 0, 0, 0, cos_theta, sin_theta, 0, 0, -sin_theta, cos_theta, 0, 0, 0, 0, 1);
  return Transform(mat, inv_mat);
}

Transform RotateY(Float theta)
{
  Float sin_theta = std::sin(Radians(theta));
  Float cos_theta = std::cos(Radians(theta));
  Matrix4 mat(cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0, cos_theta, 0, 0, 0, 0, 1);
  Matrix4 inv_mat(cos_theta, 0, -sin_theta, 0, 0, 1, 0, 0, sin_theta, 0, cos_theta, 0, 0, 0, 0, 1);
  return Transform(mat, inv_mat);
}

Transform RotateZ(Float theta)
{
  Float sin_theta = std::sin(Radians(theta));
  Float cos_theta = std::cos(Radians(theta));
  Matrix4 mat(cos_theta, 0, sin_theta, 0, 0, 1, 0, 0, -sin_theta, 0, cos_theta, 0, 0, 0, 0, 1);
  Matrix4 inv_mat(cos_theta, -sin_theta, 0, 0, sin_theta, cos_theta, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  return Transform(mat, inv_mat);
}

const Transform Transform::operator*(const Transform& rhs) const
{
  return Transform(Matrix4::Mul(mat_, rhs.mat_), Matrix4::Mul(inv_mat_, rhs.inv_mat_));
}

} // namespace leptus