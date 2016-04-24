#ifndef LEPTUS_NORMAL_H
#define LEPTUS_NORMAL_H

#include "core/leptus.h"

namespace leptus {

template <typename T>
class Normal3 {
public:
  T x_, y_, z_;

public:
  Normal3() { x_ = y_ = z_ = 0; }
  Normal3(T x_, T y_, T z_) : x_(x_), y_(y_), z_(z_) { Assert(!HasNaNs()); }
  explicit Normal3<T>(const Vector3<T>& v) : x_(v.x_), y_(v.y_), z_(v.z_)
  {
    Assert(!v.HasNaNs());
  }

  Normal3<T> operator-() const { return Normal3(-x_, -y_, -z_); }

  Normal3<T> operator+(const Normal3<T>& n) const
  {
    Assert(!n.HasNaNs());
    return Normal3<T>(x_ + n.x_, y_ + n.y_, z_ + n.z_);
  }

  Normal3<T> & operator+=(const Normal3<T>& n)
  {
    Assert(!n.HasNaNs());
    x_ += n.x_;
    y_ += n.y_;
    z_ += n.z_;
    return *this;
  }

  Normal3<T> operator-(const Normal3<T>& n) const
  {
    Assert(!n.HasNaNs());
    return Normal3<T>(x_ - n.x_, y_ - n.y_, z_ - n.z_);
  }

  Normal3<T> & operator-=(const Normal3<T>& n)
  {
    Assert(!n.HasNaNs());
    x_ -= n.x_;
    y_ -= n.y_;
    z_ -= n.z_;
    return *this;
  }

  template <typename U>
  Normal3<T> operator*(U f) const
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
  Normal3<T> operator/(U f) const
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

  T operator[](int i) const
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

  bool HasNaNs() const { return IsNaN(x_) || IsNaN(y_) || IsNaN(z_); }
  Float LengthSquared() const { return x_ * x_ + y_ * y_ + z_ * z_; }
  Float Length() const { return std::sqrt(LengthSquared()); }

  friend std::ostream& operator<<(std::ostream& os, const Normal3<T>& v)
  {
    os << "[" << v.x_ << ", " << v.y_ << ", " << v.z_ << "]";
    return os;
  }
};

typedef Normal3<Float> Normal3f;

}  // namespace leptus


#endif // LEPTUS_NORMAL_H