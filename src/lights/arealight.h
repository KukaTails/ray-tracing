#ifndef LEPTUS_LIGHTS_AREALIGHT_H
#define LEPTUS_LIGHTS_AREALIGHT_H

#include "core/light.h"
#include "core/surface.h"
#include "materials/emissive.h"

namespace leptus {

class AreaLight : public Light {
public:
  AreaLight(const Emissive& emissive_material = Emissive(Color(1.0, 1.0, 1.0)));
  AreaLight(const SurPtr& surface, const Emissive& emissive_material = Emissive(Color(1.0, 1.0, 1.0)));
  void SetSurface(const SurPtr& surface);
  void SetEmissvieMaterial(const Emissive& material);
  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const override;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const override;
  virtual Color light(const ShadeRecord& shade_rec) const override;
  virtual Float GeometricFactor(const HitRecord& hit_rec) const override;
  virtual Float ProbabilityDensityFunction(const HitRecord& hit_rec) const override;

private:
  SurPtr surface_;
  Emissive emissive_material_;
  mutable Point3f sample_point_;
  mutable Normal3f sample_normal_;
  mutable Vector3f in_dir_;
};


} // namespace leptus

#endif // LEPTUS_LIGHT_AREALIGHT_H