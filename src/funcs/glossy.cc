#include "funcs/glossy.h"

#include "geometry/geometry.h"

namespace leptus {

GlossySpecular::GlossySpecular(Float k_specular, const Color& color, Float exp)
  : k_specular_(k_specular), c_specular_(color), exp_(exp)
{}

Color GlossySpecular::Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const
{
  return BLACK;
}

Color GlossySpecular::F(const HitRecord& hit_rec,
                        const Vector3f& in_dir,
                        const Vector3f& out_dir) const
{
  Color out_color;
  Float n_dot_in = Dot(hit_rec.n_hit_, in_dir);
  Vector3f refl_dir = -in_dir + 2 * Vector3f(hit_rec.n_hit_ * n_dot_in);
  Float refl_dot_out = Dot(refl_dir, out_dir);

  if (refl_dot_out > 0.0)
    out_color = k_specular_ * pow(refl_dot_out, exp_);
  return out_color;
}

Color GlossySpecular::SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const
{
  return BLACK;
}

} // namespace leptus