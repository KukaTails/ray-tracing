#ifndef LEPTUS_SPECULAR_H
#define LEPTUS_SPECULAR_H

#include "core/color.h"
#include "core/func.h"

namespace leptus {

class PerfectSpecular : Func {
private:
  Float k_refl_;
  Color c_refl_;

public:
  PerfectSpecular(const Color& color, Float k_refl);
  virtual Color Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const override;
  virtual Color F(const HitRecord& hit_rec,
                  const Vector3f& in_dir,
                  const Vector3f& out_dir) const override;
  virtual Color SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const override;
};


} // namespace leptus

#endif // LEPTUS_SPECULAR_H