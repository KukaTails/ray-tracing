#ifndef LEPTUS_VEC_H
#define LEPTUS_VEC_H

#include "core/leptus.h"

namespace leptus {

template <typename T>
class Vector2 {
public:
  T x_, y_;

public:
  Vector2():x_(0), y_(0) { }
  Vector2(T x, T y) : x_(x), y_(y) { Assert(!HasNaNs()); }
  bool HasNaNs() const { return IsNaN(x_) || IsNaN(y_); }
  explicit Vector2(const Point2<T>& p);
  explicit Vector2(const Point3<T>& p);

  friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
  {
    os << "[" << v.x_ << ", " << v.y_ << "]";
    return os;
  }

  Vector2<T> operator+(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Vector2(x_ + v.x_, y_ + v.y_);
  }

  Vector2<T>& operator+=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ += v.x_;
    y_ += v.y_;
    return *this;
  }
  Vector2<T> operator-(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Vector2(x_ - v.x, y_ - v.y_);
  }

  Vector2<T>& operator-=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
  }

  bool operator==(const Vector2<T>& v) const { return x_ == v.x_ && y_ == v.y_; }
  bool operator!=(const Vector2<T>& v) const { return x_ != v.x_ || y_ != v.y_; }

  template <typename U>
  Vector2<T> operator*(U f) const
  {
    return Vector2<T>(f * x_, f * y_);
  }

  template <typename U>
  Vector2<T>& operator*=(U f)
  {
    Assert(!IsNaN(f));
    x_ *= f;
    y_ *= f;
    return *this;
  }

  template <typename U>
  Vector2<T> operator/(U f) const
  {
    Assert(f != 0);
    Float inv = (Float)1 / f;
    return Vector2<T>(x_ * inv, y_ * inv);
  }

  template <typename U>
  Vector2<T>& operator/=(U f)
  {
    Assert(f != 0);
    Float inv = (Float)1 / f;
    x_ *= inv;
    y_ *= inv;
    return *this;
  }

  Vector2<T> operator-() const { return Vector2<T>(-x_, -y_); }

  T operator[](int i) const
  {
    Assert(i >= 0 && i <= 1);
    if (i == 0) return x_;
    return y_;
  }

  T& operator[](int i)
  {
    Assert(i >= 0 && i <= 1);
    if (i == 0) return x_;
    return y_;
  }

  Float LengthSquared() const { return x_ * x + y_ * y; }
  Float Length() const { return std::sqrt(LengthSquared()); }
};

template <typename T>
Vector2<T>::Vector2(const Point2<T>& p)
  :x_(p.x_), y_(p.y_)
{}

template <typename T>
Vector2<T>::Vector2(const Point3<T>& p)
  : x_(p.x_), y_(p.y_)
{}

template <typename T>
class Vector3 {
public:
  T x_, y_, z_;

public:
  Vector3() { x_ = y_ = z_ = T(0); }
  Vector3(T x) { x_ = y_ = z_ = x; }
  Vector3(T x, T y, T z) : x_(x), y_(y), z_(z) { Assert(!HasNaNs()); }
  explicit Vector3(const Point3<T>& p);
  explicit Vector3(const Normal3<T>& n);

  bool HasNaNs() const { return IsNaN(x_) || IsNaN(y_) || IsNaN(z_); }

  friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
  {
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
  }

  Vector3<T> operator+(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Vector3(x_ + v.x_, y_ + v.y__, z_ + v.z_);
  }

  Vector3<T>& operator+=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ += v.x_;
    y_ += v.y__;
    z_ += v.z_;
    return *this;
  }

  Vector3<T> operator-(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs());
    return Vector3(x - v.x_, y_ - v.y__, z_ - v.z_);
  }

  Vector3<T>& operator-=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ -= v.x_;
    y_ -= v.y__;
    z_ -= v.z_;
    return *this;
  }

  bool operator==(const Vector3<T>& v) const
  {
    return x_ == v.x_ && y_ == v.y__ && z_ == v.z_;
  }

  bool operator!=(const Vector3<T>& v) const
  {
    return x_ != v.x_ || y_ != v.y__ || z_ == v.z_;
  }

  template <typename U>
  Vector3<T> operator*(U s) const
  {
    return Vector3<T>(s * x_, s * y_, s * z_);
  }

  template <typename U>
  Vector3<T> operator*=(U s) const
  {
    Assert(!IsNaN(s));
    x_ *= s;
    y_ *= s;
    z_ *= s;
    return *this;
  }

  template <typename U>
  Vector3<T> operator/(U f) const
  {
    Assert(f != 0);
    Float inv = static_cast<Float>(1) / f;
    return Vector3(x_ * inv, y_ * inv, z_ * inv);
  }


  template <typename U>
  Vector3<T> operator/=(U f) const
  {
    Assert(f != 0);
    Float inv = static_cast<Float>(1) / f;
    x_ *= inv;
    y_ *= inv;
    z_ *= inv;
    return *this;
  }

  T operator[](int i) const
  {
    Assert(i >= 0 && i <= 2);
    if (i == 0) return x_;
    if (i == 1) return y_;
    return z_;
  }

  T& operator[](int i)
  {
    Assert(i >= 0 && i <= 2);
    if (i == 0) return x_;
    if (i == 1) return y_;
    return z_;
  }

  Vector3<T> operator-() const { return Vector3<T>(-x_, -y_, -z_); }
  Float LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_; }
  Float Length() const { return std::sqrt(LengthSquared()); }
};


typedef Vector2<Float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

} // namespace leptus

#endif // RAY_TRACING_VEC_H