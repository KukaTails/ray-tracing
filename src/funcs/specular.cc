#include "funcs/specular.h"

#include  "geometry/geometry.h"

namespace leptus {

PerfectSpecular::PerfectSpecular(const Color& color, Float k_refl)
  : k_refl_(k_refl), c_refl_(color)
{}

Color PerfectSpecular::Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const
{
  return BLACK;
}

Color PerfectSpecular::F(const HitRecord& hit_rec, const Vector3f& in_dir, const Vector3f& out_dir) const
{
  return BLACK;
}

Color PerfectSpecular::SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const
{
  Float n_dot_out = Dot(hit_rec.n_hit_, out_dir);
  in_dir = -out_dir + 2.0 * Vector3f(hit_rec.n_hit_) * n_dot_out;

  return k_refl_ * c_refl_ * (1.0 /Dot(hit_rec.n_hit_, in_dir));
}

} // namespace leptus