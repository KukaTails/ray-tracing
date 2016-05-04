#include "tracers/whitted.h"

#include "core/debuger.h"

namespace leptus {

const int Whitted::MAX_DEPTH = 3;

Color Whitted::TraceRay(const World& world, const Ray& ray) const
{
  return TraceRay(world, ray, 0);
}

Color Whitted::TraceRay(const World& world, const Ray& ray, const int depth) const
{
  if (depth > MAX_DEPTH) {
    return BLACK;
  } else {
    ShadeRecord shade_rec = world.HitObjects(ray);
    if (Debuger::NOW_X == Debuger::CAPTURED_X && Debuger::NOW_Y == Debuger::CAPTURED_Y) {
      std::cout << "Depth: " << depth << std::endl;
      std::cout << "Is hit: " << shade_rec.is_hit_ << std::endl;
      std::cout << "Hit point: " << shade_rec.hit_rec_.p_hit_ << std::endl;
      std::cout << "Hit n_hit: " << shade_rec.hit_rec_.n_hit_ << std::endl;
      std::cout << "Hit material: " << shade_rec.material_ << std::endl;
      std::cout << "ray: dir=" << ray.dir_ << " point: " << ray.orig_ << std::endl;
    }
    if (shade_rec.is_hit_) {
      shade_rec.hit_rec_.depth_ = depth;
      shade_rec.ray_ = ray;
      if (Debuger::NOW_X == Debuger::CAPTURED_X && Debuger::NOW_Y == Debuger::CAPTURED_Y)
        std::cout << "ray: dir=" << shade_rec.ray_.dir_ << " point: " << shade_rec.ray_.orig_ << std::endl;
      return shade_rec.material_->Shade(shade_rec);
    } else {
      return world.bg_color_;
    }
  }
}

} // namespace leptus