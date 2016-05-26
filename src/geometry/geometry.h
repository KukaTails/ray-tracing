#ifndef LEPTUS_GEOMETRY_H
#define LEPTUS_GEOMETRY_H
#include <ostream>
#include "core/leptus.h"

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

template <typename T> class Point2;
template <typename T> class Point3;
template <typename T> class Vector2;
template <typename T> class Vector3;
template <typename T> class Normal3;

template <typename T>
class Point2 {
public:
  T x_, y_;

public:
  Point2( ) : x_(0), y_(0) { }
  Point2(T x, T y) : x_(x), y_(y) { Assert(!HasNaNs( )); }
  explicit Point2(const Point3<T>& p);

  template <typename U>
  explicit Point2(const Point2<U>& p)
  {
    x_ = (T)p.x_;
    y_ = (T)p.y_;
    Assert(!HasNaNs( ));
  }

  template <typename U>
  explicit Point2(const Vector2<U>& p);

  friend std::ostream& operator<<(std::ostream& os, const Point2<T>& p)
  {
    os << "[" << p.x_ << ", " << p.y_ << "]";
    return os;
  }

  const Point2<T> operator+(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Point2<T>(x_ + v.x_, y_ + v.y_);
  }

  Point2<T>& operator+=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ += v.x_;
    y_ += v.y_;
    return *this;
  }

  const Vector2<T> operator-(const Point2<T>& p) const
  {
    Assert(!p.HasNaNs( ));
    return Vector2<T>(x_ - p.x_, y_ - p.y_);
  }

  const Point2<T> operator-(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Point2<T>(x_ - v.x_, y_ - v.y_);
  }

  const Point2<T> operator-( ) const { return Point2<T>(-x_, -y_); }
  Point2<T>& operator-=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
  }

  Point2<T>& operator+=(const Point2<T>& p)
  {
    Assert(!p.HasNaNs( ));
    x_ += p.x_;
    y_ += p.y_;
    return *this;
  }

  const Point2<T> operator+(const Point2<T>& p) const
  {
    Assert(!p.HasNaNs( ));
    return Point2<T>(x_ + p.x_, y_ + p.y);
  }

  template <typename U>
  const Point2<T> operator*(U f) const
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
  const Point2<T> operator/(U f) const
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

  const T operator[](int i) const
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
  bool HasNaNs( ) const { return IsNaN(x_) || IsNaN(y_); }
};


template <typename T>
class Point3 {
public:
  T x_, y_, z_;

public:
  Point3( ) { x_ = y_ = z_ = 0; }
  Point3(T x, T y, T z) : x_(x), y_(y), z_(z) { Assert(!HasNaNs( )); }

  template <typename U>
  explicit Point3(const Point3<U>& p)
    : x_(T(p.x_)), y_(T(p.y_)), z_(T(p.z_))
  {
    Assert(!HasNaNs( ));
  }

  template <typename U>
  explicit operator Vector3<U>( ) const
  {
    return Vector3<U>(x_, y_, z_);
  }

  friend std::ostream& operator<<(std::ostream& os, const Point3<T>& p)
  {
    os << "[" << p.x_ << ", " << p.y_ << ", " << p.z_ << "]";
    return os;
  }

  const Point3<T> operator+(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Point3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
  }

  const Point3<T> operator+(const Point3<T>& p) const
  {
    Assert(!v.HasNaNs( ));
    return Point3(x_ + p.x_, y_ + p.y_, z_ + p.z_);
  }

  Point3<T>& operator+=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;
    return *this;
  }

  Point3<T>& operator+=(const Point3<T>& p)
  {
    Assert(!p.HasNaNs( ));
    x_ += p.x_;
    y_ += p.y_;
    z_ += p.z_;
    return *this;
  }

  const Vector3<T> operator-(const Point3<T>& p) const
  {
    Assert(!p.HasNaNs( ));
    return Vector3<T>(x_ - p.x_, y_ - p.y_, z_ - p.z_);
  }

  const Point3<T> operator-(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Point3<T>(x_ - v.x_, y - v.y_, z_ - v.z_);
  }

  Point3<T>& operator-=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
  }

  template <typename U>
  const Point3<T> operator*(U f) const
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
  const Point3<T> operator/(U f) const
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

  const T operator[](int i) const
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

  const Point3<T> operator-( ) const { return Vector3<T>(-x_, -y_, -z_); }

  bool HasNaNs( ) const { return IsNaN(x_) || IsNaN(y_) || IsNaN(z_); }
};

typedef Point2<int> Point2i;
typedef Point2<Float> Point2f;
typedef Point3<int> Point3i;
typedef Point3<Float> Point3f;



template <typename T>
class Vector2 {
public:
  T x_, y_;

public:
  Vector2( ) :x_(0), y_(0) { }
  Vector2(T x, T y) : x_(x), y_(y) { Assert(!HasNaNs( )); }
  bool HasNaNs( ) const { return IsNaN(x_) || IsNaN(y_); }
  explicit Vector2(const Point2<T>& p);
  explicit Vector2(const Point3<T>& p);

  friend std::ostream& operator<<(std::ostream& os, const Vector2<T>& v)
  {
    os << "[" << v.x_ << ", " << v.y_ << "]";
    return os;
  }

  const Vector2<T> operator+(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Vector2(x_ + v.x_, y_ + v.y_);
  }

  Vector2<T>& operator+=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ += v.x_;
    y_ += v.y_;
    return *this;
  }

  const Vector2<T> operator-(const Vector2<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Vector2(x_ - v.x, y_ - v.y_);
  }

  Vector2<T>& operator-=(const Vector2<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
  }

  bool operator==(const Vector2<T>& v) const { return x_ == v.x_ && y_ == v.y_; }
  bool operator!=(const Vector2<T>& v) const { return x_ != v.x_ || y_ != v.y_; }

  template <typename U>
  const Vector2<T> operator*(U f) const
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
  const Vector2<T> operator/(U f) const
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

  const Vector2<T> operator-( ) const
  {
    return Vector2<T>(-x_, -y_);
  }

  const T operator[](int i) const
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

  Float LengthSquared( ) const { return x_ * x + y_ * y; }
  Float Length( ) const { return std::sqrt(LengthSquared( )); }
};

template <typename T>
Vector2<T>::Vector2(const Point2<T>& p)
  :x_(p.x_), y_(p.y_)
{ }

template <typename T>
Vector2<T>::Vector2(const Point3<T>& p)
  : x_(p.x_), y_(p.y_)
{ }

template <typename T>
class Vector3 {
public:
  T x_, y_, z_;

public:
  Vector3( ) { x_ = y_ = z_ = T(0); }
  Vector3(T x) { x_ = y_ = z_ = x; }
  Vector3(T x, T y, T z) : x_(x), y_(y), z_(z) { Assert(!HasNaNs( )); }
  explicit Vector3(const Point3<T>& p);
  explicit Vector3(const Normal3<T>& n);

  bool HasNaNs( ) const { return IsNaN(x_) || IsNaN(y_) || IsNaN(z_); }

  friend std::ostream& operator<<(std::ostream& os, const Vector3<T>& v)
  {
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
  }

  const Vector3<T> operator+(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Vector3(x_ + v.x_, y_ + v.y_, z_ + v.z_);
  }

  Vector3<T>& operator+=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ += v.x_;
    y_ += v.y__;
    z_ += v.z_;
    return *this;
  }

  const Vector3<T> operator-(const Vector3<T>& v) const
  {
    Assert(!v.HasNaNs( ));
    return Vector3(x_ - v.x_, y_ - v.y_, z_ - v.z_);
  }

  Vector3<T>& operator-=(const Vector3<T>& v)
  {
    Assert(!v.HasNaNs( ));
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;
    return *this;
  }

  bool operator==(const Vector3<T>& v) const
  {
    return x_ == v.x_ && y_ == v.y_ && z_ == v.z_;
  }

  bool operator!=(const Vector3<T>& v) const
  {
    return x_ != v.x_ || y_ != v.y_ || z_ == v.z_;
  }

  template <typename U>
  const Vector3<T> operator*(U s) const
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
  const Vector3<T> operator/(U f) const
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

  const T operator[](int i) const
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

  const Vector3<T> operator-( ) const { return Vector3<T>(-x_, -y_, -z_); }
  Float LengthSquared( ) const { return x_ * x_ + y_ * y_ + z_ * z_; }
  Float Length( ) const { return std::sqrt(LengthSquared( )); }
};


typedef Vector2<Float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector3<Float> Vector3f;
typedef Vector3<int> Vector3i;

template <typename T>
class Normal3 {
public:
  T x_, y_, z_;

public:
  Normal3( ) { x_ = y_ = z_ = 0; }
  Normal3(T x_, T y_, T z_) : x_(x_), y_(y_), z_(z_) { Assert(!HasNaNs( )); }
  explicit Normal3<T>(const Vector3<T>& v) : x_(v.x_), y_(v.y_), z_(v.z_)
  {
    Assert(!v.HasNaNs( ));
  }

  const Normal3<T> operator-( ) const { return Normal3(-x_, -y_, -z_); }

  const Normal3<T> operator+(const Normal3<T>& n) const
  {
    Assert(!n.HasNaNs( ));
    return Normal3<T>(x_ + n.x_, y_ + n.y_, z_ + n.z_);
  }

  Normal3<T>& operator+=(const Normal3<T>& n)
  {
    Assert(!n.HasNaNs( ));
    x_ += n.x_;
    y_ += n.y_;
    z_ += n.z_;
    return *this;
  }

  const Normal3<T> operator-(const Normal3<T>& n) const
  {
    Assert(!n.HasNaNs( ));
    return Normal3<T>(x_ - n.x_, y_ - n.y_, z_ - n.z_);
  }

  Normal3<T> & operator-=(const Normal3<T>& n)
  {
    Assert(!n.HasNaNs( ));
    x_ -= n.x_;
    y_ -= n.y_;
    z_ -= n.z_;
    return *this;
  }

  template <typename U>
  const Normal3<T> operator*(U f) const
  {
    return Normal3<T>(f * x_, f * y_, f * z_);
  }

  template <typename U>
  Normal3<T>& operator*=(U f)
  {
    x_ *= f;
    y_ *= f;
    z_ *= f;
    return *this;
  }

  template <typename U>
  const Normal3<T> operator/(U f) const
  {
    Assert(f != 0);
    Float inv = (Float)1 / f;
    return Normal3<T>(x_ * inv, y_ * inv, z_ * inv);
  }

  template <typename U>
  Normal3<T>& operator/=(U f)
  {
    Assert(f != 0);
    Float inv = (Float)1 / f;
    x_ *= inv;
    y_ *= inv;
    z_ *= inv;
    return *this;
  }

  bool operator==(const Normal3<T>& n) const
  {
    return x_ == n.x_ && y_ == n.y_ && z_ == n.z_;
  }

  bool operator!=(const Normal3<T>& n) const
  {
    return x_ != n.x_ || y_ != n.y_ || z_ != n.z_;
  }

  const T operator[](int i) const
  {
    Assert(i >= 0 & & i <= 2);
    if (i == 0) return x_;
    if (i == 1) return y_;
    return z_;
  }

  T& operator[](int i)
  {
    Assert(i >= 0 & & i <= 2);
    if (i == 0) return x_;
    if (i == 1) return y_;
    return z_;
  }

  bool HasNaNs( ) const { return IsNaN(x_) || IsNaN(y_) || IsNaN(z_); }
  Float LengthSquared( ) const { return x_ * x_ + y_ * y_ + z_ * z_; }
  Float Length( ) const { return std::sqrt(LengthSquared( )); }

  friend std::ostream& operator<<(std::ostream& os, const Normal3<T>& v)
  {
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
  }
};

typedef Normal3<Float> Normal3f;




template <typename T>
Point2<T>::Point2(const Point3<T>& p)
  : x_(p.x_), y_(p.y_)
{
  Assert(!HasNaNs( ));
}

template <typename T>
template <typename U>
Point2<T>::Point2(const Vector2<U>& p)
{
  x_ = (T)p.x_;
  y_ = (T)p.y_;
  Assert(!HasNaNs( ));
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
inline const Point3<T> operator*(U f, const Point3<T> &p)
{
  Assert(!p.HasNaNs());
  return p * f;
}

template <typename T, typename U>
inline const Vector3<T> operator*(U s, const Vector3<T>& v)
{
  return v * s;
}

template <typename T>
inline Float Distance(const Point3<T>& v1, const Point3<T>& v2)
{
  Float x_dis = abs(v2.x_ - v1.x_);
  Float y_dis = abs(v2.y_ - v1.y_);
  return sqrt(x_dis * x_dis + y_dis * y_dis);
}

template <typename T>
inline const Vector3<T> Cross(const Vector3<T>& v1, const Vector3<T>& v2)
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
inline const Vector3<T> Normalize(const Vector3<T>& v)
{
  return v / v.Length();
}

template <typename T>
inline const Normal3<T> Normalize(const Normal3<T>& n)
{
  return n / n.Length();
}

} // namespace leptus

#endif // LEPTUS_GEOMETRY_H 
