#include "surfaces/disk.h"

#include "geometry/geometry.h"

namespace leptus {

const Float Disk::EPSILON = 1e-4;

Disk::Disk(const Point3f& center, Float radius, const Normal3f& n)
  : center_(center), radius_(radius), n_(Normalize(n))
{}

bool Disk::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  Float t = Dot((center_ - ray.orig_), n_) / Dot(ray.dir_, n_);
  if (abs(t) <= EPSILON)
    return false;

  Point3f p_hit = ray.orig_ + t * ray.dir_;
  Float distance = Distance(p_hit, center_);
  if (distance < radius_) {
    t_hit = t;
    hit_rec.n_hit_ = n_;
    hit_rec.p_hit_ = p_hit;
    return true;
  }
  return false;
}

} // namespace leptus