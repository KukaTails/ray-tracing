#include "surfaces/instance.h"

#include "geometry/geometry.h"
#include "geometry/transform.h"

namespace leptus {

Instance::Instance(const SurPtr& surface)
  : surface_(surface), transform_( ), is_texture_transformed_(false)
{ }

void Instance::TransformTexture(bool option)
{
  is_texture_transformed_ = option;
}

void Instance::Translate(Float x, Float y, Float z)
{
  transform_ = transform_ * leptus::Translate(x, y, z);
}

void Instance::Scale(Float x, Float y, Float z)
{
  transform_ = transform_ * leptus::Scale(x, y, z);
}

void Instance::RotateX(Float radians)
{
  Assert(0 <= radians && radians <= 2 * M_PI);
  transform_ = transform_ * leptus::RotateX(radians);
}

void Instance::RotateY(Float radians)
{
  Assert(0 <= radians && radians <= 2 * M_PI);
  transform_ = transform_ * leptus::RotateY(radians);
}

void Instance::RotateZ(Float radians)
{
  Assert(0 <= radians && radians <= 2 * M_PI);
  transform_ = transform_ * leptus::RotateZ(radians);
}

void Instance::Rotate(Float x_radians, Float y_radians, Float z_radians)
{
  Assert(0 <= x_radians && x_radians <= 2 * M_PI);
  Assert(0 <= y_radians && y_radians <= 2 * M_PI);
  Assert(0 <= z_radians && z_radians <= 2 * M_PI);
  RotateX(x_radians);
  RotateY(y_radians);
  RotateZ(z_radians);
}

bool Instance::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  Ray inv_ray = transform_(ray);

  if (surface_->Hit(inv_ray, t_hit, hit_rec)) {
    hit_rec.p_hit_ = transform_.Trans(hit_rec.p_hit_);
    hit_rec.n_hit_ = Normalize(transform_.InvTrans(hit_rec.n_hit_));
    material_ = surface_->material( );
    if (!is_texture_transformed_)
      hit_rec.local_p_hit_ = ray.orig_ + t_hit * ray.dir_;
    return true;
  }
  return false;
}

bool Instance::ShadowHit(const Ray& ray, Float& t_hit) const
{
  return Hit(ray, t_hit, HitRecord( ));
}

Point3f Instance::GetLocalHitPoint(const Point3f& p_hit) const
{
  return transform_.Trans(p_hit);
}

} // namespace leptus