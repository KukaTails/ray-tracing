#include "textures/mapping.h"

namespace leptus {

Point2f SphericalMapping::GetTextureCoordinates(const Point3f& local_hit_point) const
{
  Float theta = acos(local_hit_point.y_);
  Float phi = atan2(local_hit_point.x_, local_hit_point.z_);
  if (phi < 0)
    phi += 2 * M_PI;
  Float u = phi / (2 * M_PI);
  Float v = theta * INV_PI;
  return Point2f(u, v);
}

Point2f RectanglelMapping::GetTextureCoordinates(const Point3f& local_hit_point) const
{
  Float u = (local_hit_point.x_ + 1) / 2.0f;
  Float v = (-local_hit_point.z_ + 1) / 2.0f;
  return Point2f(u, v);
}

} // namespace leptus