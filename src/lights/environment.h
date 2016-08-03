#ifndef LEPTUS_LIGHTS_ENVIRONMENT_H
#define LEPTUS_LIGHTS_ENVIRONMENT_H
#include "core/light.h"
#include "materials/emissive.h"

namespace leptus {

class EnvironmentLight : public Light {
public:
  EnvironmentLight(const Emissive& emissive_material);
  EnvironmentLight(const Emissive& emissive_material, const SamplerPtr& sampler);
  void SetSamplers(const SamplerPtr& sampler);
  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const override;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const override;
  virtual Color light(const ShadeRecord& shade_rec) const override;
  void SetEmissvieMaterial(const Emissive& material);
  virtual Float ProbabilityDensityFunction(const HitRecord& hit_rec) const override;

private:
  Emissive emissive_material_;
  SamplerPtr sampler_;
  mutable Vector3f u_, v_, w_;
  mutable Vector3f sample_point_;
};

} // namespace leptus

#endif // LEPTUS_LIGHTS_ENVIRONMENT_H