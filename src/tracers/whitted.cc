#include "tracers/whitted.h"

#include "core/shaderecord.h"

namespace leptus {

const int WhittedTracer::MAX_DEPTH = 3;

Color WhittedTracer::TraceRay(const World& world, const Ray& ray) const
{
  return TraceRay(world, ray, 0);
}

Color WhittedTracer::TraceRay(const World& world, const Ray& ray, const int depth) const
{
  if (depth > MAX_DEPTH) {
    return BLACK;
  } else {
    ShadeRecord shade_rec(world.HitObjects(ray), *this);
    if (shade_rec.is_hit_) {
      shade_rec.hit_rec_.depth_ = depth;
      shade_rec.ray_ = ray;
      return shade_rec.material_->Shade(shade_rec);
    } else {
      return world.backgroud_color();
    }
  }
}

} // namespace leptus