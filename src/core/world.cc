#include "core/world.h"

#include <limits>
#include "core/shaderecord.h"
#include "lights/ambient.h"

namespace leptus {

World::World( ) : World(WHITE)
{ }

World::World(const Color& background_color)
  : bg_color_(background_color), ambient_light_(std::make_shared<Ambient>( ))
{ }

Color World::backgroud_color( ) const
{
  return bg_color_;
}

LightPtr World::ambient_light( ) const
{
  return ambient_light_;
}

const std::vector<LightPtr>& World::lights( ) const
{
  return lights_;
}

const std::vector<SurPtr>& World::surfaces( ) const
{
  return surfaces_;
}

void World::AddSurface(const SurPtr& surface)
{
  Assert(surface);
  surfaces_.push_back(surface);
}

void World::AddLight(const LightPtr& light)
{
  Assert(light);
  lights_.push_back(light);
}

ShadeRecord World::HitObjects(const Ray& ray) const
{
  ShadeRecord shade_rec(*this);
  Float t_hit, t_min = std::numeric_limits<Float>::max();
  HitRecord hit_rec;
  
  for (int i = 0; i < surfaces_.size(); ++i) {
    if (surfaces_[i]->Hit(ray, t_hit, hit_rec) && (t_hit < t_min)) {
      t_min = t_hit;
      shade_rec.is_hit_ = true;
      shade_rec.material_ = surfaces_[i]->material();
      shade_rec.hit_rec_ = hit_rec;
    }
  }
  return shade_rec;
}

}  // namespace leptus