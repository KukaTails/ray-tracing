#ifndef LEPTUS_POINT_H
#define LEPTUS_POINT_H

#include "core/leptus.h"

namespace leptus {

template <typename T>
class Point2 {
public:
  T x_, y_;

public:
  Point2(): x_(0), y_(0) {}
  Point2(T x, T y) : x_(x), y_(y) { Assert(!HasNaNs()); }
  explicit Point2(const Point3<T>& p) : x_(p.x_), y_(p.y_) { Assert(!HasNaNs()); }

  template <typename U>
  explicit Point2(const Point2<U>& p)
  {
    x_ = (T)p.x_;
    y_ = (T)p.y_;
    Assert(!HasNaNs());
  }

  template <typename U>
  explicit Point2(const Vector2<U>& p)
  {
    x_ = (T)p.x_;
    y_ = (T)p.y_;
    Assert(!HasNaNs());
  }

  template <typename U>
  explicit operator Vector2<U>() const
  {
    return Vector2<U>(x_, y_);
  }

  friend std::ostream& operator<<(std::ostream& os, const Point2<T>& p)
  {
    os << "[" << p.x_ << ", " << p.y_ << "]";
    return os;
  }

  Point2<T> operator+(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Point2<T>(x_ + v.x_, y_ + v.y_);
  }

  Point2<T>& operator+=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ += v.x_;
    y_ += v.y_;
    return *this;
  }

  Vector2<T> operator-(const Point2<T>& p) const
  {
    Assert(!p.HasNaNs());
    return Vector2<T>(x_ - p.x_, y_ - p.y_);
  }

  Point2<T> operator-(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Point2<T>(x_ - v.x_, y_ - v.y_);
  }

  Point2<T> operator-() const { return Point2<T>(-x_, -y_); }
  Point2<T>& operator-=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
  }

  Point2<T>& operator+=(const Point2<T>& p)
  {
    Assert(!p.HasNaNs());
    x_ += p.x_;
    y_ += p.y_;
    return *this;
  }

  Point2<T> operator+(const Point2<T>& p) const
  {
    Assert(!p.HasNaNs());
    return Point2<T>(x_ + p.x_, y_ + p.y);
  }

  template <typename U>
  Point2<T> operator*(U f) const
  {
    return Point2<T>(f * x_, f * y_);
  }
  template <typename U>
  Point2<T>& operator*=(U f)
  {
    x_ *= f;
    y_ *= f;
    return *this;
  }

  template <typename U>
  Point2<T> operator/(U f) const
  {
    Float inv = (Float)1 / f;
    return Point2<T>(inv * x_, inv * y_);
  }

  template <typename U>
  Point2<T>& operator/=(U f)
  {
    Float inv = (Float)1 / f;
    x_ *= inv;
    y_ *= inv;
    return *this;
  }

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

  bool operator==(const Point2<T>& p) const { return x_ == p.x_ && y_ == p.y; }
  bool operator!=(const Point2<T>& p) const { return x_ != p.x_ || y_ != p.y; }
  bool HasNaNs() const { return IsNaN(x_) || IsNaN(y_); }
};


template <typename T>
class Point3 {
public:
  T x_, y_, z_;

public:
  Point3() { x_ = y_ = z_ = 0; }
  Point3(T x, T y, T z) : x_(x), y_(y), z_(z) { Assert(!HasNaNs()); }
  
  template <typename U>
  explicit Point3(const Point3<U>& p)
    : x_(T(p.x_)), y_(T(p.y_)), z_(T(p.z_))
  {
    Assert(!HasNaNs());
  }

  template <typename U>
  explicit operator Vector3<U>() const
  {
    return Vector3<U>(x_, y_, z_);
  }

  friend std::ostream& operator<<(std::ostream& os, const Point3<T>& p)
  {
    os << "[" << p.x_ << ", " << p.y_ << ", " << p.z_ << "]";
    return os;
  }

  Point3<T> operator+(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Point3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
  }
 
  Point3<T> operator+(const Point3<T>& p) const
  {
    Assert(!v.HasNaNs());
    return Point3(x_ + p.x_, y_ + p.y_, z_ + p.z_);
  }

  Point3<T>& operator+=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
  }

  Point3<T>& operator+=(const Point3<T>& p)
  {
    Assert(!p.HasNaNs());
    x_ += p.x_;
    y_ += p.y_;
    z_ += p.z_;
    return *this;
  }

  Vector3<T> operator-(const Point3<T>& p) const
  {
    Assert(!p.HasNaNs());
    return Vector3<T>(x_ - p.x_, y_ - p.y_, z_ - p.z_);
  }

  Point3<T> operator-(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs());
    return Point3<T>(x_ - v.x_, y - v.y_, z_ - v.z_);
  }

  Point3<T>& operator-=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs());
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
  }

  template <typename U>
  Point3<T> operator*(U f) const
  {
    return Point3<T>(f * x_, f * y_, f * z_);
  }

  template <typename U>
  Point3<T> operator*=(U f) const
  {
    Assert(!IsNaN(f));
    x_ *= f;
    y_ *= f;
    z_ *= f;
    return *this;
  }

  template <typename U>
  Point3<T> operator/(U f) const
  {
    Assert(f != 0);
    Float inv = static_cast<Float>(1) / f;
    return Point3<T>(inv * x_, inv * y_, inv * z_);
  }

  template <typename U>
  Point3<T> operator/=(U f) const
  {
    Assert(f != 0);
    Float inp = static_cast<Float>(1) / f;
    x_ *= inp;
    y_ *= inp;
    z_ *= inp;
    return *this;
  }

  T operator[](int i) const
  {
    Assert(i >= 0 && i <= 2);
    if (i == 0) return x_;
    if (i == 1) return y_;
    return z_;
  }

  bool operator==(const Point3<T>& p) const
  {
    return x_ == p.x_ && y_ == p.y_ && z_ == p.z_;
  }

  bool operator!=(const Point3<T>& p) const
  {
    return x_ != p.x_ || y_ != p.y_ || z_ == p.z_;
  }

  Point3<T> operator-() const { return Vector3<T>(-x_, -y_, -z_); }

  bool HasNaNs() const { return IsNaN(x_) || IsNaN(y_) || IsNaN(z_); }
};

typedef Point2<int> Point2i;
typedef Point2<Float> Point2f;
typedef Point3<int> Point3i;
typedef Point3<Float> Point3f;

}  // namespace leptus

#endif // LEPTUS_POINT_H
