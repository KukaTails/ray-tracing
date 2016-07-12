#ifndef LEPTUS_ACCELERATE_BOUNDING_BOX_H
#define LEPTUS_ACCELERATE_BOUNDING_BOX_H
#include <memory>
#include "accelerate/bounding_box.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class BoundingBox {
public:
  using BoundingBoxPtr = std::shared_ptr<BoundingBox>;

public:
  BoundingBox(const Point3f& min, const Point3f& max);
  bool Hit(const Ray& ray) const;

public:
  Point3f min_, max_;
};

using BoundingBoxPtr = BoundingBox::BoundingBoxPtr;

} // namespace leptus

#endif // LEPTUS_ACCELERATE_BOUNDING_BOX_H