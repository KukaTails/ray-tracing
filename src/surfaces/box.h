#ifndef LEPTUS_BOX_H
#define LEPTUS_BOX_H

#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class Box {
public:
  Point3f min_, max_;

public:
  Box(const Point3f& min, const Point3f& max);
  bool Hit(const Ray& ray) const;
};


} // namespace leptus

#endif // LEPTUS_BOX_H