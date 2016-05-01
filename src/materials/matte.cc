#include "materials/matte.h"

#include "geometry/geometry.h"
#include "world/world.h"

namespace leptus {

Matte::Matte(const Color& color)
  : ambient_func_(0.5, color), diffuse_func_(0.8, color)
{}

Matte::Matte(const Color& color, Float k_ambient, Float k_diffuse)
  : ambient_func_(k_ambient, color), diffuse_func_(k_diffuse, color)
{}

Color Matte::Shade(const ShadeRecord& shade_rec) const
{
  const HitRecord& hit_rec = shade_rec.hit_rec_;
  const std::vector<LightPtr>& lights = shade_rec.world_.lights_;

  Vector3f out_dir = -shade_rec.ray_.dir_;
  Color out_color = ambient_func_.Rho(shade_rec.hit_rec_, out_dir) * shade_rec.world_.ambient_light_->light();

  for (int i = 0; i < lights.size(); ++i) {
    Vector3f in_dir = lights[i]->GetShadowRayDir(shade_rec.hit_rec_);
    Float n_dot_in = Dot(hit_rec.n_hit_ , in_dir);
    Float n_dot_out = Dot(hit_rec.n_hit_, out_dir);

    if (lights[i]->CastShadows() && !lights[i]->InShadow(hit_rec.p_hit_, shade_rec.world_.objects_)) {
      if (n_dot_in > static_cast<Float>(0.0) && n_dot_out > static_cast<Float>(0.0))
        out_color += diffuse_func_.F(hit_rec, in_dir, out_dir) * shade_rec.world_.lights_[i]->light() * n_dot_in;
    }
  }
  return out_color;
}

} // namespace leptus