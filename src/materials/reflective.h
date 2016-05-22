#ifndef LEPTUS_REFLECTIVE_H
#define LEPTUS_REFLECTIVE_H

#include "core/shaderecord.h"
#include "funcs/specular.h"
#include "materials/phong.h"

namespace leptus {

class Reflective : public Phong {
private:
  PerfectSpecular refl_func_;

public:
  Reflective(const Color& color, Float k_refl = 0.7,
             Float k_specular = 0.6, Float exp = 20,
             Float k_diffuse = 0.8, Float k_ambient = 0.5);
  Reflective(const Lambertian& ambient_func,
             const Lambertian& diffuse_func,
             const GlossySpecular& specular_func,
             const PerfectSpecular& refl_func);
  virtual Color Shade(const ShadeRecord& shade_rec) const override;
};

} // namespace leptus

#endif // LEPTUS_REFLECTIVE_H 