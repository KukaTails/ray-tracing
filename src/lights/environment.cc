#include "lights/environment.h"
#include "samplers/jitter.h"

namespace leptus {

EnvironmentLight::EnvironmentLight(const Emissive& emissive_material)
  : Light(), emissive_material_(emissive_material), sampler_(std::make_shared<JitterSampler>(9, 2))
{ }


EnvironmentLight::EnvironmentLight(const Emissive& emissive_material, const SamplerPtr& sampler)
  : Light(), emissive_material_(emissive_material), sampler_(sampler)
{ }


void EnvironmentLight::SetSamplers(const SamplerPtr& sampler)
{
  Assert(sampler);
  sampler_ = sampler;
}


void EnvironmentLight::SetEmissvieMaterial(const Emissive& material)
{
  emissive_material_ = material;
}


Vector3f EnvironmentLight::GetShadowRayDir(const HitRecord& hit_rec) const
{
  w_ = Normalize(static_cast<Vector3f>(hit_rec.n_hit_));
  v_ = Normalize(Cross(Vector3f(0.0034, 1.0, 0.0071), w_));
  u_ = Normalize(Cross(v_, w_));

  Point3f sample_point = sampler_->SampleUnitHemiSphere( );
  sample_point_ = sample_point.x_ * u_ + sample_point.y_ * v_ + sample_point.z_ * w_;
  return sample_point_;
}


Color EnvironmentLight::light(const ShadeRecord& shade_rec) const
{
  return emissive_material_.light(shade_rec.hit_rec_);
}


bool EnvironmentLight::InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const
{
  const Point3f sample_point = static_cast<Point3f>(sample_point_);
  Float t_hit = std::numeric_limits<Float>::max( );
  Float d = Distance(point, sample_point);
  Ray ray(point, Normalize(sample_point - point));

  for (int i = 0; i < objects.size( ); ++i) {
    if (objects[i]->ShadowHit(ray, t_hit) && t_hit < d) {
      return true;
    }
  }
  return false;
}

Float EnvironmentLight::ProbabilityDensityFunction(const HitRecord& hit_rec) const
{
  Float cos_theta = sample_point_.y_;
  return cos_theta / M_PI;
}

} // namespace leptus