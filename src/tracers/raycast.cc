#include "tracers/raycast.h"

#include "core/shaderecord.h"
#include "world/world.h"

namespace leptus {

Color RayCast::TraceRay(const World& world, const Ray& ray) const
{
  ShadeRecord shade_rec = world.HitObjects(ray);

  if (shade_rec.is_hit_) {
    shade_rec.ray_ = ray;
    return shade_rec.material_->Shade(shade_rec);
  } else {
    return world.bg_color_;
  }
}

Color RayCast::TraceRay(const World& world, const Ray& ray, const int depth) const
{
  ShadeRecord shade_rec = world.HitObjects(ray);
  if (shade_rec.is_hit_) {
    shade_rec.ray_ = ray;
    return shade_rec.material_->Shade(shade_rec);
  } else {
    return world.bg_color_;
  }
}

Color RayCast::TraceRay(const World& world, const Ray& ray, const int depth, int& count, int& jump) const
{
  ShadeRecord shade_rec = world.HitObjects(ray);
  
  if (shade_rec.is_hit_) {
    shade_rec.ray_ = ray;
    return shade_rec.material_->Shade(shade_rec);
  } else {
    return world.bg_color_;
  }
}

} // namespace leptus