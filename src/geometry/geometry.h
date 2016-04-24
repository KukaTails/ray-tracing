#ifndef LEPTUS_GEOMETRY_H
#define LEPTUS_GEOMETRY_H

#include "vec.h"
#include "point.h"
#include "normal.h"

namespace leptus {

template <typename T>
inline bool IsNaN(const T x)
{
  return std::isnan(x);
}

template <>
inline bool IsNaN(const int x)
{
  return false;
}

template <typename T>
inline Vector3<T>::Vector3(const Normal3<T>& n)
  : x_(n.x_), y_(n.y_), z_(n.z_)
{
  Assert(!n.HasNaNs());
}

template <typename T>
inline Vector3<T>::Vector3(const Point3<T>& p)
  : x_(p.x_), y_(p.y_), z_(p.z_)
{
  Assert(!p.HasNaNs());
}

template <typename T>
inline T Dot(const Vector3<T>& v, const Normal3<T>& n)
{
  Assert(!v.HasNaNs() && !n.HasNaNs());
  return v.x_ * n.x_ + v.y_ * n.y_ + v.z_ * n.z_;
}

template <typename T>
inline T Dot(const Normal3<T>& n, const Vector3<T>& v)
{
  Assert(!v.HasNaNs() && !n.HasNaNs());
  return v.x_ * n.x_ + v.y_ * n.y_ + v.z_ * n.z_;
}

template <typename T>
inline T Dot(const Normal3<T> &n1, const Normal3<T> &n2)
{
  Assert(!n1.HasNaNs() && !n2.HasNaNs());
  return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T, typename U>
inline Point3<T> operator*(U f, const Point3<T> &p)
{
  Assert(!p.HasNaNs());
  return p * f;
}

template <typename T, typename U>
inline Vector3<T> operator*(U s, const Vector3<T>& v)
{
  return v * s;
}

template <typename T>
inline Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2)
{
  Assert(!v1.HasNaNs() && !v2.HasNaNs());
  double v1x = v1.x_, v1y = v1.y_, v1z = v1.z_;
  double v2x = v2.x_, v2y = v2.y_, v2z = v2.z_;
  return Vector3<T>((v1y * v2z) - (v1z * v2y),
                    (v1z * v2x) - (v1x * v2z),
                    (v1x * v2y) - (v1y * v2x));
}

template <typename T>
inline T Dot(const Vector3<T>& v1, const Vector3<T>& v2)
{
  Assert(!v1.HasNaNs() && !v2.HasNaNs());
  return v1.x_ * v2.x_ + v1.y_ * v2.y_ + v1.z_ * v2.z_;
}

template <typename T>
inline T AbsDot(const Vector3<T>& v1, const Vector3<T>& v2)
{
  Assert(!v1.HasNaNs() && !v2.HasNaNs());
  return std::abs(Dot(v1, v2));
}

template <typename T>
inline Vector3<T> Normalize(const Vector3<T>& v)
{
  return v / v.Length();
}

template <typename T>
inline Normal3<T> Normalize(const Normal3<T>& n)
{
  return n / n.Length();
}

} // namespace leptus

#endif // LEPTUS_GEOMETRY_H 
