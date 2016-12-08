#ifndef LEPTUS_MATERIAL_WARD_H
#define LEPTUS_MATERIAL_WARD_H

#include "core/color.h"
#include "core/leptus.h"
#include "core/material.h"
#include "core/shaderecord.h"
#include "brdfs/lambertian.h"
#include "brdfs/wardreflection.h"

namespace leptus {

class WardMaterial : public Material {
public:
  WardMaterial(const Color& color, Float k_specular, Float exp, Float k_diffuse, Float k_ambient = 0.5);
  WardMaterial(const LambertianBRDF& ambient_func,
                const LambertianBRDF& diffuse_func,
                const WardReflectionBRDF& specular_func);
  virtual Color Shade(const ShadeRecord& shade_rec) const override;

protected:
  LambertianBRDF ambient_func_;
  LambertianBRDF diffuse_func_;
  WardReflectionBRDF specular_func_;
};

} // namespace leptus


#endif // LEPTUS_MATERIAL_WARD_H