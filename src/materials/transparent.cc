#include "materials/transparent.h"

#include <string>
#include "core/world.h"

namespace leptus {

Transparent::Transparent(const Color& color, Float refractive_index,
                         Float k_transmit /* = 0.8 */, Float k_refl /* = 0.6 */,
                         Float k_specular /* = 0.8 */, Float exp /* = 20 */,
                         Float k_diffuse /* = 0.5 */, Float k_ambient /* = 0.5 */)
  : Phong(color, k_specular, exp, k_diffuse, k_ambient), reflective_func_(color, k_refl),
  transmitter_func_(refractive_index, k_transmit)
{ }

Transparent::Transparent(const Phong& phong_material,
                         const PerfectSpecular& reflective_func,
                         const PerfectTransmitter& transmitter_func)
  : Phong(phong_material), reflective_func_(reflective_func), transmitter_func_(transmitter_func)
{ }

Color Transparent::Shade(const ShadeRecord& shade_rec) const
{
  Color out_color = Phong::Shade(shade_rec);
  Vector3f in_dir, out_dir = -shade_rec.ray_.dir_;
  Color reflected_color = reflective_func_.SampleF(shade_rec.hit_rec_, in_dir, out_dir);
  Ray reflected_ray(shade_rec.hit_rec_.p_hit_ + BIAS * in_dir, in_dir);

  if (transmitter_func_.TotalInternalReflection(shade_rec.ray_, shade_rec.hit_rec_)) {
    out_color += shade_rec.tracer_.TraceRay(shade_rec.world_, reflected_ray, shade_rec.hit_rec_.depth_ + 1);
  } else {
    Vector3f refractive_dir;
    Color refracted_color = transmitter_func_.SampleF(shade_rec.hit_rec_, out_dir, refractive_dir);
    Ray refracted_ray(shade_rec.hit_rec_.p_hit_ + BIAS * refractive_dir, refractive_dir);

    out_color += reflected_color * shade_rec.tracer_.TraceRay(shade_rec.world_, reflected_ray, shade_rec.hit_rec_.depth_ + 1) *
      fabs(Dot(shade_rec.hit_rec_.n_hit_, in_dir));
    out_color += refracted_color * shade_rec.tracer_.TraceRay(shade_rec.world_, refracted_ray, shade_rec.hit_rec_.depth_ + 1) *
      fabs(Dot(shade_rec.hit_rec_.n_hit_, refractive_dir));
  }
  return out_color;
}

} // namespace leptus