#ifndef LEPTUS_MATERIAL_MICROFACET_H
#define LEPTUS_MATERIAL_MICROFACET_H

#include "core/material.h"
#include "core/shaderecord.h"
#include "brdfs/lambertian.h"
#include "brdfs/cooktorrancereflection.h"

namespace leptus {

class MicroFacetMaterial : public Material {
public:
  MicroFacetMaterial(Float fresnel_init, Float alpha_factor, Float kd, const Color& diffuse_color, const Color& reflection_color = WHITE);
  MicroFacetMaterial(const LambertianBRDF& diffuse_func_, CookTorranceReflectionBRDF& specular_func);
  virtual Color Shade(const ShadeRecord& shade_rec) const override;

private:
  LambertianBRDF lamberatian_func_;
  CookTorranceReflectionBRDF specular_func_;
};


} // namespace leptus

#endif // LEPTUS_MATERIAL_MICROFACET_H