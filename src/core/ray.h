#ifndef LEPTUS_CORE_RAY_H
#define LEPTUS_CORE_RAY_H
#include <iostream>

#include "core/leptus.h"
#include "geometry/geometry.h"

namespace leptus {

class Ray {
public:
  Point3f orig_;
  Vector3f dir_;
  Float t_max_;

public:
  Ray() : t_max_(INFINITY_FLOAT) {}
  Ray(const Point3f& orig, const Vector3f& dir, Float t_max = INFINITY_FLOAT)
    : orig_(orig), dir_(dir) { }

  Point3f operator()(Float t) const { return orig_ + dir_ * t; }
  
  bool HasNaNs() const { return (orig_.HasNaNs() || dir_.HasNaNs() || IsNaN(t_max_)); }
  friend std::ostream& operator<<(std::ostream& os, const Ray& ray)
  {
    os << "[o=" << ray.orig_ << ", d=" << ray.dir_ << ", t_max=" << ray.t_max_ << "]";
    return os;
  }
};

} // namespace leptus

#endif // LEPTUS_RAY_H