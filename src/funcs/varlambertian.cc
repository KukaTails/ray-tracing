#include "funcs/varlambertian.h"

#include "geometry/geometry.h"

namespace leptus {

VARLambertian::VARLambertian(Float k_diffuse, const TexturePtr& c_diffuse)
  : k_diffuse_(k_diffuse), c_diffuse_(c_diffuse)
{ }

Color VARLambertian::Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const
{
  return c_diffuse_->GetColor(hit_rec) * INV_PI;
}

Color VARLambertian::F(const HitRecord& hit_rec,
                    const Vector3f& in_dir,
                    const Vector3f& out_dir) const
{
  return k_diffuse_ * c_diffuse_->GetColor(hit_rec) * INV_PI;
}

Color VARLambertian::SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const
{
  return F(hit_rec, in_dir, out_dir) * (1.0 / (Dot(hit_rec.n_hit_, in_dir)));
}

} // namespace leptus