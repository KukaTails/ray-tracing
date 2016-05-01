#include "funcs/lambertian.h"

#include "geometry/geometry.h"

namespace leptus {

Lambertian::Lambertian(Float k_diffuse, const Color& c_diffuse)
  : k_diffuse_(k_diffuse), c_diffuse_(c_diffuse)
{}

Color Lambertian::Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const
{
  return k_diffuse_ * c_diffuse_;
}

Color Lambertian::F(const HitRecord& hit_rec,
                    const Vector3f& in_dir,
                    const Vector3f& out_dir) const
{
  return k_diffuse_ * c_diffuse_ * INV_PI;
}

Color Lambertian::SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const
{
  return F(hit_rec, in_dir, out_dir) * (1.0 / (Dot(hit_rec.n_hit_, in_dir)));
}

} // namespace leptus