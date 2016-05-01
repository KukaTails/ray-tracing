#ifndef LEPTUS_LAMBERTIAN_H
#define LEPTUS_LAMBERTIAN_H

#include "core/leptus.h"
#include "core/color.h"
#include "core/func.h"

namespace leptus {

class Lambertian : public Func {
private:
  Float k_diffuse_;
  Color c_diffuse_;
public:
  Lambertian(Float k_diffuse, const Color& c_diffuse);
  virtual Color Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const override;
  virtual Color F(const HitRecord& hit_rec,
                  const Vector3f& in_dir,
                  const Vector3f& out_dir) const override;
  virtual Color SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const override;
};

} // namespace leptus

#endif // LEPTUS_LAMBERTIAN_H