#ifndef LEPTUS_LIGHTS_AMBIENT_H
#define LEPTUS_LIGHTS_AMBIENT_H

#include "core/light.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class Ambient : public Light {
public:
  Ambient();
  Ambient(Color color, Float light_scale = static_cast<Float>(1.0));
  Ambient(Float light_scale, Color color = WHITE);
  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const override;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const override;
  virtual Color light(const ShadeRecord& shader_rec) const override;

private:
  Color color_;
  Float light_scale_;
};

} // namespace leptus

#endif // LEPTUS_LIGHTS_AMBIENT_H