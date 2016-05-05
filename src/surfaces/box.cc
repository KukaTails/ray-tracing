#include "surfaces/box.h"

namespace leptus {

Box::Box(const Point3f& min, const Point3f& max)
  : min_(min), max_(max)
{}

bool Box::Hit(const Ray& ray) const
{
  return false;
}


} // namespace leptus