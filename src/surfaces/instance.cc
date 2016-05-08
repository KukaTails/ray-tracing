#include "surfaces/instance.h"

#include "geometry/geometry.h"

namespace leptus {

bool Instance::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  Ray inv_ray = transform_(ray);

  if (surface_->Hit(inv_ray, t_hit, hit_rec)) {
    hit_rec.p_hit_ = transform_(hit_rec.p_hit_);
    hit_rec.n_hit_ = Normalize(transform_(hit_rec.n_hit_));
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

} // namespace leptus