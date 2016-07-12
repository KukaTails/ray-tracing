#include "materials/emissive.h"
#include "geometry/geometry.h"
#include "core/shaderecord.h"

namespace leptus {

Emissive::Emissive(const Color& color, Float ls /* = 0.5f */)
  : color_(color), ls_(ls)
{ }


Color Emissive::light(const HitRecord& hit_rec) const
{
  return ls_ * color_;
}

void Emissive::setColor(const Color& color)
{
  color_ = color;
}

void Emissive::scaleRadiance(Float scaling_factor)
{
  ls_ = scaling_factor;
}

Color Emissive::Shade(const ShadeRecord& shade_rec) const
{
  if (-Dot(shade_rec.hit_rec_.n_hit_, shade_rec.ray_.dir_) > 0.0)
    return light(shade_rec.hit_rec_);
  else
    return Color(0.0f, 0.0f, 0.0f);
}


Color Emissive::AreaLightShade(const ShadeRecord& shade_rec) const
{
  if (-Dot(shade_rec.hit_rec_.n_hit_, shade_rec.ray_.dir_) > 0.0)
    return light(shade_rec.hit_rec_);
  else
    return Color(0.0f, 0.0f, 0.0f);
}

} // namespace leptus