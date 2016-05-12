#ifndef LEPTUS_CORE_WORLD_H
#define LEPTUS_CORE_WORLD_H
#include <vector>

#include "core/color.h"
#include "core/ray.h"
#include "core/light.h"
#include "core/surface.h"

namespace leptus {

class World {
public:
  typedef std::shared_ptr<World> WorldPtr;
private:
  Color bg_color_;
  LightPtr ambient_light_;
  std::vector<LightPtr> lights_;
  std::vector<SurPtr> surfaces_;

public:
  World( );
  World(const Color& background_color);
  
  void AddLight(const LightPtr& light);
  void AddSurface(const SurPtr& surface);
  ShadeRecord HitObjects(const Ray& ray) const;
  Color backgroud_color( ) const;
  LightPtr ambient_light( ) const;
  const std::vector<LightPtr>& lights( ) const;
  const std::vector<SurPtr>& surfaces( ) const;
};

typedef World::WorldPtr WorldPtr;

}  // namespace leptus

#endif // LEPTUS_CORE_WORLD_H
