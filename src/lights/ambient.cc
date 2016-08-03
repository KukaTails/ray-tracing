#include "lights/ambient.h"

namespace leptus {

Ambient::Ambient()
  : Light(false), color_(WHITE), light_scale_(static_cast<Float>(1.0))
{}

Ambient::Ambient(Float light_scale, Color color /* = WHITE */)
  : Light(false), color_(color), light_scale_(light_scale)
{}

Ambient::Ambient(Color color, Float light_scale /* = static_cast<Float>(1.0) */)
  : Light(false), color_(color), light_scale_(light_scale)
{}

Color Ambient::light(const ShadeRecord& shader_rec) const
{
  return light_scale_ * color_;
}

bool Ambient::InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const
{
  return false;
}

Vector3f Ambient::GetShadowRayDir(const HitRecord& hit_record) const
{
  return Vector3f(static_cast<Float>(0));
}

} // namespace leptus