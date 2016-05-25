#include "surfaces/sphere.h"

namespace leptus {

Sphere::Sphere(const Point3f& center, Float radius, const Color& color)
  : center_(center), radius_(radius), Surface(color)
{}

Sphere::Sphere(const Point3f& center, Float radius, const MaterialPtr& material)
  : center_(center), radius_(radius), Surface(material)
{}

Point3f Sphere::GetLocalHitPoint(const Point3f& p_hit) const
{
  return Point3f((p_hit.x_ - center_.x_) / radius_,
                 (p_hit.y_ - center_.y_) / radius_,
                 (p_hit.z_ - center_.z_) / radius_);
}

bool Sphere::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  /*
  Vector3f l = center_ - ray.orig_;
  Float tca = Dot(l, ray.dir_);
  if (tca < 0) return false;

  Float d2 = Dot(l, l) - tca * tca;
  if (d2 > radius_ * radius_)
    return false;
  
  Float thc = sqrt(radius_ * radius_- d2);
  Float t0 = tca - thc, t1 = tca + thc;
  if (t0 < 0)
    t0 = t1;
  if (t0 < 0)
    return false;
  t_hit = t0;
  */
  if (ShadowHit(ray, t_hit)) {
    hit_rec.p_hit_ = ray.orig_ + ray.dir_ * t_hit;
    hit_rec.n_hit_ = Normal3f(Normalize(hit_rec.p_hit_ - center_));
    hit_rec.local_p_hit_ = GetLocalHitPoint(hit_rec.p_hit_);
    return true;
  }
  return false;
}

bool Sphere::ShadowHit(const Ray& ray, Float& t_hit) const
{
  Vector3f l = center_ - ray.orig_;
  Float tca = Dot(l, ray.dir_);
  if (tca < 0) return false;

  Float d2 = Dot(l, l) - tca * tca;
  if (d2 > radius_ * radius_)
    return false;

  Float thc = sqrt(radius_ * radius_ - d2);
  Float t0 = tca - thc, t1 = tca + thc;
  if (t0 < 0)
    t0 = t1;
  if (t0 < 0)
    return false;
  t_hit = t0;

  return true;
}

} // namespace leptus