#include "pointlight.h"

#include "geometry/geometry.h"

namespace leptus {

PointLight::PointLight(const Point3f& location)
  :location_(location), color_(WHITE), light_scale_(static_cast<Float>(1.0))
{}

PointLight::PointLight(const Point3f& location,
                       const Color& color,
                       Float ligth_scale /* = static_cast<Float>(1.0) */)
  : location_(location), color_(color), light_scale_(ligth_scale)
{}

PointLight::PointLight(const Point3f& location,
                       Float ligth_scale,
                       const Color& color /* = WHITE */)
  : location_(location), color_(color), light_scale_(ligth_scale)
{}

Color PointLight::light() const
{
  return light_scale_ * color_;
}

bool PointLight::CastShadows() const
{
  return true;
}

Vector3f PointLight::GetShadowRayDir(const HitRecord& hit_rec) const
{
  return Normalize(location_ - hit_rec.p_hit_);
}

bool PointLight::InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const
{
  Float t_hit = std::numeric_limits<Float>::max();
  Float d = Distance(point, location_);
  Ray ray(point, Normalize(location_ - point));

  for (int i = 0; i < objects.size(); ++i) {
    if (objects[i]->ShadowHit(ray, t_hit) && t_hit < d) {
      return true;
    }
  }
  return false;
}

} // namespace light