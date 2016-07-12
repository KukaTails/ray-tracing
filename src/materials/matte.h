#ifndef LEPTUS_MATTM_H
#define LEPTUS_MATTM_H

#include "core/color.h"
#include "core/material.h"
#include "core/shaderecord.h"
#include "funcs/lambertian.h"

namespace leptus {

class Matte : public Material {
private:
  Lambertian ambient_func_;
  Lambertian diffuse_func_;

public:
  Matte(const Color& color);
  Matte(const Color& color, Float k_ambient, Float k_diffuse);
  virtual Color Shade(const ShadeRecord& shade_rec) const;
  virtual Color AreaLightShade(const ShadeRecord& shade_rec) const;
};

} // namespace leptus

#endif // LEPTUS_MATTM_H
