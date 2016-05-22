#include "materials/reflective.h"

#include "core/hitrecord.h"
#include "core/shaderecord.h"
#include "core/world.h"

namespace leptus {

Reflective::Reflective(const Color& color, Float k_refl /* = 0.7 */,
                       Float k_specular /* = 0.6 */, Float exp /* = 20 */,
                       Float k_diffuse /* = 0.8 */, Float k_ambient /* = 0.5 */)
  : Phong(color, k_specular, exp, k_diffuse, k_ambient), refl_func_(color, k_refl)
{}

Reflective::Reflective(const Lambertian& ambient_func,
                       const Lambertian& diffuse_func,
                       const GlossySpecular& specular_func,
                       const PerfectSpecular& refl_func)
  : Phong(ambient_func, diffuse_func, specular_func), refl_func_(refl_func)
{}

Color Reflective::Shade(const ShadeRecord& shade_rec) const
{
  Color color(Phong::Shade(shade_rec));

  Vector3f in_dir;
  Vector3f out_dir = -shade_rec.ray_.dir_;
  HitRecord hit_rec = shade_rec.hit_rec_;
  Color refl_color = refl_func_.SampleF(shade_rec.hit_rec_, in_dir, out_dir);
  Ray refl_ray(shade_rec.hit_rec_.p_hit_, in_dir);

  color += refl_color * shade_rec.tracer_.TraceRay(shade_rec.world_, refl_ray, hit_rec.depth_ + 1) *
    Dot(in_dir, shade_rec.hit_rec_.n_hit_);
  return color;
}

} // namespace leptus