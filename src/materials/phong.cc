#include "materials/phong.h"

#include "core/world.h"
#include "geometry/geometry.h"

namespace leptus {

Phong::Phong(const Color& color,
             Float k_specular, Float exp,
             Float k_diffuse, Float k_ambient /* = 0.5 */)
  : ambient_func_(k_ambient, color), diffuse_func_(k_diffuse, color),
  specular_func_(k_specular, color, exp)
{}

Phong::Phong(const Lambertian& ambient_func,
             const Lambertian& diffuse_func,
             const GlossySpecular& specular_func)
  : ambient_func_(ambient_func), diffuse_func_(diffuse_func), specular_func_(specular_func)
{}


Color Phong::Shade(const ShadeRecord& shade_rec) const
{
  const HitRecord& hit_rec = shade_rec.hit_rec_;
  const std::vector<LightPtr>& lights = shade_rec.world_.lights();

  Vector3f out_dir = -shade_rec.ray_.dir_;
  Color out_color = ambient_func_.Rho(hit_rec, out_dir) * shade_rec.world_.ambient_light()->light();

  for (int i = 0; i < lights.size(); ++i) {
    Vector3f in_dir = lights[i]->GetShadowRayDir(shade_rec.hit_rec_);
    Float n_dot_in = Dot(hit_rec.n_hit_, in_dir);

    if (n_dot_in > 0.0) {
      if (lights[i]->CastShadows() && !lights[i]->InShadow(hit_rec.p_hit_, shade_rec.world_.surfaces())) {
        out_color += (diffuse_func_.F(hit_rec, out_dir, in_dir)
                      + specular_func_.F(hit_rec, out_dir, in_dir)) *
          shade_rec.world_.lights()[i]->light() * n_dot_in;
      }
    }
  }
  return out_color;
}

} // namespace leptus