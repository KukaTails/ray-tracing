#ifndef LEPTUS_PHONG_H
#define LEPTUS_PHONG_H

#include "core/color.h"
#include "core/leptus.h"
#include "core/material.h"
#include "core/shaderecord.h"
#include "funcs/glossy.h"
#include "funcs/lambertian.h"

namespace leptus {

class Phong : public Material {
private:
  Lambertian ambient_func_;
  Lambertian diffuse_func_;
  GlossySpecular specular_func_;

public:
  Phong(const Color& color, Float k_specular, Float exp, Float k_diffuse, Float k_ambient = 0.5);
  Phong(const Lambertian& ambient_func,
        const Lambertian& diffuse_func,
        const GlossySpecular& specular_func);
  virtual Color Shade(const ShadeRecord& shade_rec) const override;
};

} // namespace leptus


#endif // LEPTUS_PHONG_H