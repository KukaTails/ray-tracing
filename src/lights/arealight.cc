#include "lights/arealight.h"
#include "geometry/geometry.h"

namespace leptus {

AreaLight::AreaLight(const Emissive& emissive_material /* = Emissive(Color(1.0, 1.0, 1.0)) */)
  : Light(), surface_( ), emissive_material_(emissive_material)
{ }


AreaLight::AreaLight(const SurPtr& surface, const Emissive& emissive_material /* = Emissive(Color(1.0, 1.0, 1.0)) */)
  : Light(), surface_(surface), emissive_material_(emissive_material)
{}


void AreaLight::SetSurface(const SurPtr& surface)
{
  Assert(surface != nullptr);
  surface_ = surface;
}


void AreaLight::SetEmissvieMaterial(const Emissive& material)
{
  emissive_material_ = material;
}


Color AreaLight::light(const ShadeRecord& shade_rec) const
{
  if (-Dot(sample_normal_, in_dir_) > 0.0) {
    return emissive_material_.light(shade_rec.hit_rec_);
  } else {
    return Color(0.0f, 0.0f, 0.0f);
  }
}


Vector3f AreaLight::GetShadowRayDir(const HitRecord& hit_rec) const
{
  sample_point_ = surface_->Sample();
  sample_normal_ = surface_->GetNormal(sample_point_);
  in_dir_ = sample_point_ - hit_rec.p_hit_;
  return Normalize(in_dir_);
}


bool AreaLight::InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const
{
  Float t_hit = std::numeric_limits<Float>::max( );
  Float d = Distance(point, sample_point_);
  Ray ray(point, Normalize(sample_point_ - point));

  for (int i = 0; i < objects.size( ); ++i) {
    if (objects[i]->ShadowHit(ray, t_hit) && t_hit < d) {
      return true;
    }
  }
  return false;
}


Float AreaLight::GeometricFactor(const HitRecord& hit_rec) const
{
  Float n_dot_d = -Dot(sample_normal_, in_dir_);
  Float distance = Distance(sample_point_, hit_rec.p_hit_);
  return n_dot_d / (distance * distance);
}


Float AreaLight::ProbabilityDensityFunction(const HitRecord& hit_rec) const
{
  return surface_->ProbabilityDensityFunc(hit_rec);
}

} // namespace leptus