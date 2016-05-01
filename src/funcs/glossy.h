#ifndef LEPTUS_GLOSSY_SPECULAR_H
#define LEPTUS_GLOSSY_SPECULAR_H

#include "core/color.h"
#include "core/func.h"

namespace leptus {

class GlossySpecular : public Func {
private:
  Float k_specular_, exp_;
  Color c_specular_;
public:
  GlossySpecular(Float k_specular, const Color& color, Float exp);
  virtual Color Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const override;
  virtual Color F(const HitRecord& hit_rec,
                  const Vector3f& in_dir,
                  const Vector3f& out_dir) const override;
  virtual Color SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const override;
};

} // namespace leptus

#endif // LEPTUS_GLOSSY_SPECULAR_H