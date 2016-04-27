#include "core/ray.h"
#include "surfaces/sphere.h"
#include "geometry/geometry.h"

namespace leptus {

Sphere::Sphere(const Point3f& center, Float radius, const Color& color)
  : center_(center), radius_(radius), Surface(color)
{}

Sphere::Sphere(const Point3f& center, Float radius, const MaterialPtr& material)
  : center_(center), radius_(radius), Surface(material)
{}

bool Sphere::Hit(const Ray& ray, Float& t_hit, ShadeRecord& shade_rec) const
{
  Vector3f l = center_ - ray.orig_;
  Float tca = Dot(l, ray.dir_);
  if (tca < 0) return false;

  Float d2 = Dot(l, l) - tca * tca;
  if (d2 > radius_ * radius_) return false;
  
  Float thc = sqrt(radius_ * radius_- d2);
  Float t0 = tca - thc, t1 = tca + thc;
  if (t0 < 0)
    t0 = t1;
  t_hit = t0;
  shade_rec.p_hit_ = ray.orig_ + ray.dir_ * t0;
  shade_rec.n_hit_ = Normal3f(Normalize(shade_rec.p_hit_ - center_));
  return true;
}

} // namespace leptus