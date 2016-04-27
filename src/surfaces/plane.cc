#include "surfaces/plane.h"

#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {
const Float Plane::EPSILON = 1e-4;

Plane::Plane(const Point3f& p, const Normal3f& n, const Color& color /* = BLACK */)
  : p_(p), n_(n), Surface(color)
{}

Plane::Plane(const Point3f& p, const Normal3f& n, const MaterialPtr& material)
  : p_(p), n_(n), Surface(material)
{}

bool Plane::Hit(const Ray& ray, Float& t_hit, ShadeRecord& shade_rec) const
{
  Float t = Dot(p_ - ray.orig_, n_) / Dot(ray.dir_, n_);
  if (t > EPSILON) {
    t_hit = t;
    shade_rec.n_hit_ = n_;
    shade_rec.p_hit_ = ray.orig_ + ray.dir_ * t;
    return true;
  }
  return false;
}

} // namespace leptus