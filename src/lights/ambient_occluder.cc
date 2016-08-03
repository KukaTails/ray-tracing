#include "lights/ambient_occluder.h"

#include "core/color.h"
#include "samplers/jitter.h"

namespace leptus {

AmbientOcculuder::AmbientOcculuder(const Color& color)
  : color_(color), sampler_(std::make_shared<JitterSampler>(16, 4)), min_amount_(Color(0.2, 0.2, 0.2)), light_scale_(1.0)
{ }

AmbientOcculuder::AmbientOcculuder(const Color& color, const SamplerPtr& sampler)
  : color_(color), sampler_(sampler), min_amount_(Color(0.2, 0.2, 0.2)), light_scale_(1.0)
{ }

AmbientOcculuder::AmbientOcculuder(const Color& color, const SamplerPtr& sampler, Float light_scale)
  : color_(color), sampler_(sampler), min_amount_(Color(0.2, 0.2, 0.2)), light_scale_(light_scale)
{ }

AmbientOcculuder::AmbientOcculuder(const Color& color, const SamplerPtr& sampler, const Color& min_amount)
  : color_(color), sampler_(sampler), min_amount_(min_amount), light_scale_(1.0)
{ }

AmbientOcculuder::AmbientOcculuder(const Color& color, const SamplerPtr& sampler, Float light_scale, const Color& min_amount)
  : color_(color), sampler_(sampler), light_scale_(light_scale), min_amount_(min_amount)
{ }

Vector3f AmbientOcculuder::GetShadowRayDir(const HitRecord& hit_rec) const
{
  Point3f sample_point = sampler_->SampleUnitHemiSphere( );
  return dir_ = sample_point.x_ * u_ + sample_point.y_ * v_ + sample_point.z_ * w_;
}


bool AmbientOcculuder::InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const
{
  Ray ray(point, dir_);
  Float t = leptus::INFINITY_FLOAT;
  for (int i = 0; i < objects.size( ); ++i) {
    if (objects[i]->ShadowHit(ray, t))
      return true;
  }
  return false;
}


Color AmbientOcculuder::light(const ShadeRecord& shade_rec) const
{
  const HitRecord hit_rec = shade_rec.hit_rec_;
  w_ = static_cast<Vector3f>(Normalize(hit_rec.n_hit_));
  v_ = Normalize(Cross(w_, Vector3f(0.0072, 1.0, 0.0034)));
  u_ = Normalize(Cross(v_, w_));

  Vector3f dir = GetShadowRayDir(hit_rec);
  Ray ray(hit_rec.p_hit_, dir);
  if (InShadow(hit_rec.p_hit_, shade_rec.world_.surfaces( ))) {
    return (min_amount_ * light_scale_ * color_);
  } else {
    return light_scale_ * color_;
  }
}


void AmbientOcculuder::SetSampler(const SamplerPtr& sampler)
{
  Assert(sampler);
  sampler_ = sampler;
}

void AmbientOcculuder::SetLightScale(Float light_scale)
{
  Assert(0.0 >= light_scale);
  light_scale_ = light_scale;
}


void AmbientOcculuder::SetMinAmount(const Color& min_amount)
{
  Assert(min_amount.r_ >= 0.0 && min_amount.g_ >= 0.0 && min_amount.b_ >= 0.0);
  min_amount_ = min_amount;
}

} // namespace leptus