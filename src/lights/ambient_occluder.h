#ifndef LEPTUS_LIGHTS_AMBIENT_OCCULUDER_H
#define LEPTUS_LIGHTS_AMBIENT_OCCULUDER_H
#include "core/light.h"
#include "core/sampler.h"

namespace leptus {

class AmbientOcculuder : public Light {
public:
  explicit AmbientOcculuder(const Color& color);
  AmbientOcculuder(const Color& color, const SamplerPtr& sampler);
  AmbientOcculuder(const Color& color, const SamplerPtr& sampler, Float light_scale);
  AmbientOcculuder(const Color& color, const SamplerPtr& sampler, const Color& min_amount);
  AmbientOcculuder(const Color& color, const SamplerPtr& sampler, Float light_scale, const Color& min_amount);

  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const override;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const override;
  virtual Color light(const ShadeRecord& shade_rec) const override;
  void SetSampler(const SamplerPtr& sampler);
  void SetLightScale(Float light_scale);
  void SetMinAmount(const Color& min_amount);

private:
  Color color_;
  SamplerPtr sampler_;
  Color min_amount_;
  Float light_scale_;
  mutable Vector3f u_, v_, w_;
  mutable Vector3f dir_;
};

} // namespace leptus

#endif // LEPTUS_LIGHTS_AMBIENT_OCCULUDER_H