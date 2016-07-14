#include "surfaces/plane.h"

#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

Plane::Plane(const Point3f& p, const Normal3f& n, const Color& color /* = BLACK */)
  : Surface(color), p_(p), n_(Normalize(n))
{}

Plane::Plane(const Point3f& p, const Normal3f& n, const MaterialPtr& material)
  : Surface(material), p_(p), n_(Normalize(n))
{}

Point3f Plane::GetLocalHitPoint(const Point3f& p_hit) const
{
  return Point3f(0, 0, 0);
}

BoundingBoxPtr Plane::GetBoundingBox( ) const
{
  return std::make_shared<BoundingBox>(Point3f( ), Point3f( ));
}

bool Plane::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  Float t = Dot(p_ - ray.orig_, n_) / Dot(ray.dir_, n_);
  if (t > EPSILON) {
    t_hit = t;
    hit_rec.n_hit_ = n_;
    hit_rec.p_hit_ = ray.orig_ + ray.dir_ * t;
    hit_rec.local_p_hit_ = GetLocalHitPoint(hit_rec.p_hit_);
    return true;
  }
  return false;
}

bool Plane::ShadowHit(const Ray& ray, Float& t_hit) const
{
  Float t = Dot(p_ - ray.orig_, n_) / Dot(ray.dir_, n_);
  if (t > EPSILON) {
    t_hit = t;
    return true;
  }
  return false;
}

} // namespace leptus