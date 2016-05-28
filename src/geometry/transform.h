#ifndef LEPTUS_TRANSFORM_H
#define LEPTUS_TRANSFORM_H

#include "core/leptus.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class Matrix4 {
public:
  static Matrix4 Inverse(const Matrix4& mat);
  static Matrix4 Mul(const Matrix4& lhs, const Matrix4& rhs);

public:
  Matrix4( );
  Matrix4(Float mat[4][4]);
  Matrix4::Matrix4(Float t00, Float t01, Float t02, Float t03,
                   Float t10, Float t11, Float t12, Float t13,
                   Float t20, Float t21, Float t22, Float t23,
                   Float t30, Float t31, Float t32, Float t33);
  bool operator==(const Matrix4& rhs) const;
  bool operator!=(const Matrix4& rhs) const;
public:
  Float m[4][4];
};

class Transform {
public:
  Transform( ) = default;
  Transform(const Matrix4& mat, const Matrix4& inv_mat);
  const Transform operator*(const Transform& rhs) const;

  const Ray operator()(const Ray& ray) const;

  template <typename T>
  const Point3<T> Trans(const Point3<T>& point) const;
  template <typename T>
  const Point3<T> InvTrans(const Point3<T>& point) const;
  template <typename T>
  const Vector3<T> Trans(const Vector3<T>& vec) const;
  template <typename T>
  const Vector3<T> InvTrans(const Vector3<T>& vec) const;
  template <typename T>
  const Normal3<T> Trans(const Normal3<T>& normal) const;
  template <typename T>
  const Normal3<T> InvTrans(const Normal3<T>& normal) const;

private:
  Matrix4 mat_, inv_mat_;
};


Transform Translate(Float x, Float y, Float z);
Transform Scale(Float x, Float y, Float z);
Transform RotateX(Float theta);
Transform RotateY(Float theta);
Transform RotateZ(Float theta);


inline const Ray Transform::operator()(const Ray& ray) const
{
  return Ray(InvTrans(ray.orig_), InvTrans(ray.dir_));
}


template <typename T>
inline const Point3<T> Transform::Trans(const Point3<T>& p) const
{
  T x = p.x_, y = p.y_, z = p.z_;
  T xp = mat_.m[0][0] * x + mat_.m[0][1] * y + mat_.m[0][2] * z + mat_.m[0][3];
  T yp = mat_.m[1][0] * x + mat_.m[1][1] * y + mat_.m[1][2] * z + mat_.m[1][3];
  T zp = mat_.m[2][0] * x + mat_.m[2][1] * y + mat_.m[2][2] * z + mat_.m[2][3];
  T wp = mat_.m[3][0] * x + mat_.m[3][1] * y + mat_.m[3][2] * z + mat_.m[3][3];
  Assert(wp != 0.0);
  if (wp == 1)
    return Point3<T>(xp, yp, zp);
  else
    return Point3<T>(xp, yp, zp) / wp;
}

template <typename T>
inline const Point3<T> Transform::InvTrans(const Point3<T>& p) const
{
  T x = p.x_, y = p.y_, z = p.z_;
  T xp = inv_mat_.m[0][0] * x + inv_mat_.m[0][1] * y + inv_mat_.m[0][2] * z + inv_mat_.m[0][3];
  T yp = inv_mat_.m[1][0] * x + inv_mat_.m[1][1] * y + inv_mat_.m[1][2] * z + inv_mat_.m[1][3];
  T zp = inv_mat_.m[2][0] * x + inv_mat_.m[2][1] * y + inv_mat_.m[2][2] * z + inv_mat_.m[2][3];
  T wp = inv_mat_.m[3][0] * x + inv_mat_.m[3][1] * y + inv_mat_.m[3][2] * z + inv_mat_.m[3][3];
  Assert(wp != 0.0);
  if (wp == 1)
    return Point3<T>(xp, yp, zp);
  else
    return Point3<T>(xp, yp, zp) / wp;
}


template <typename T>
inline const Vector3<T> Transform::Trans(const Vector3<T>& vec) const
{
  T x = vec.x_, y = vec.y_, z = vec.z_;
  T xv = mat_.m[0][0] * x + mat_.m[0][1] * y + mat_.m[0][2] * z;
  T yv = mat_.m[1][0] * x + mat_.m[1][1] * y + mat_.m[1][2] * z;
  T zv = mat_.m[2][0] * x + mat_.m[2][1] * y + mat_.m[2][2] * z;
  return Vector3<T>(xv, yv, zv);
}

template <typename T>
inline const Vector3<T> Transform::InvTrans(const Vector3<T>& vec) const
{
  T x = vec.x_, y = vec.y_, z = vec.z_;
  T xv = inv_mat_.m[0][0] * x + inv_mat_.m[0][1] * y + inv_mat_.m[0][2] * z;
  T yv = inv_mat_.m[1][0] * x + inv_mat_.m[1][1] * y + inv_mat_.m[1][2] * z;
  T zv = inv_mat_.m[2][0] * x + inv_mat_.m[2][1] * y + inv_mat_.m[2][2] * z;
  return Vector3<T>(xv, yv, zv);
}

template <typename T>
inline const Normal3<T> Transform::Trans(const Normal3<T>& normal) const
{
  T x = normal.x_, y = normal.y_, z = normal.z_;
  T xn = mat_.m[0][0] * x + mat_.m[1][0] * y + mat_.m[2][0] * z;
  T yn = mat_.m[0][1] * x + mat_.m[1][1] * y + mat_.m[2][1] * z;
  T zn = mat_.m[0][2] * x + mat_.m[1][2] * y + mat_.m[2][2] * z;
  return Normal3<T>(xn, yn, zn);
}

template <typename T>
inline const Normal3<T> Transform::InvTrans(const Normal3<T>& normal) const
{
  T x = normal.x_, y = normal.y_, z = normal.z_;
  T xn = inv_mat_.m[0][0] * x + inv_mat_.m[1][0] * y + inv_mat_.m[2][0] * z;
  T yn = inv_mat_.m[0][1] * x + inv_mat_.m[1][1] * y + inv_mat_.m[2][1] * z;
  T zn = inv_mat_.m[0][2] * x + inv_mat_.m[1][2] * y + inv_mat_.m[2][2] * z;
  return Normal3<T>(xn, yn, zn);
}

} // namespace leptus

#endif // LEPTUS_TRANSFORM_H