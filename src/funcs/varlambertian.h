#ifndef LEPTUS_VARLAMBERTIAN_H
#define LEPTUS_VARLAMBERTIAN_H

#include "core/leptus.h"
#include "core/color.h"
#include "core/func.h"
#include "core/texture.h"

namespace leptus {

class VARLambertian : public Func {
private:
  Float k_diffuse_;
  TexturePtr c_diffuse_;
public:
  VARLambertian(Float k_diffuse, const TexturePtr& c_diffuse);
  virtual Color Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const override;
  virtual Color F(const HitRecord& hit_rec,
                  const Vector3f& in_dir,
                  const Vector3f& out_dir) const override;
  virtual Color SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const override;
};

} // namespace leptus

#endif // LEPTUS_VARLAMBERTIAN_H