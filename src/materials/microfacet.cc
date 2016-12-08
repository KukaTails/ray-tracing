#include "materials/microfacet.h"

namespace leptus {

MicroFacetMaterial::MicroFacetMaterial(Float fresnel_init, Float alpha_factor, Float kd, const Color& diffuse_color, const Color& reflection_color /* = WHITE */)
  : lamberatian_func_(kd, diffuse_color),
  specular_func_(fresnel_init, alpha_factor)
{ }


MicroFacetMaterial::MicroFacetMaterial(const LambertianBRDF& diffuse_func_, CookTorranceReflectionBRDF& specular_func)
  : lamberatian_func_(diffuse_func_), specular_func_(specular_func)
{ }


Color MicroFacetMaterial::Shade(const ShadeRecord& shade_rec) const
{
  const HitRecord& hit_rec = shade_rec.hit_rec_;
  const std::vector<LightPtr>& lights = shade_rec.world_.lights();

  Vector3f out_dir = -shade_rec.ray_.dir_;
  Color L_out;

  for (int i = 0; i < lights.size(); ++i) {
    Vector3f in_dir = lights[i]->GetShadowRayDir(shade_rec.hit_rec_);
    Float n_dot_in = Dot(hit_rec.n_hit_, in_dir);

    if (n_dot_in > 0.0) {
      if (!lights[i]->InShadow(hit_rec.p_hit_, shade_rec.world_.surfaces())) {
        L_out += lamberatian_func_.Rho(hit_rec, out_dir) * shade_rec.world_.ambient_light()->light(shade_rec) * n_dot_in;
        L_out += specular_func_.F(hit_rec, in_dir, out_dir) * lights[i]->light(shade_rec) * n_dot_in;
      }
    }
  }
  return L_out;
}

} // namespace leptus