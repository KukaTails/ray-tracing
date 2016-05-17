#ifndef LEPTUS_VARMATTE_H
#define LEPTUS_VARMATTE_H

#include "core/color.h"
#include "core/material.h"
#include "core/shaderecord.h"
#include "funcs/varlambertian.h"

namespace leptus {

class VARMatte : public Material {
private:
  VARLambertian ambient_func_;
  VARLambertian diffuse_func_;

public:
  VARMatte(const TexturePtr& texture);
  VARMatte(const TexturePtr& texture, Float k_ambient, Float k_diffuse);
  virtual Color Shade(const ShadeRecord& shade_rec) const;
};

} // namespace leptus

#endif // LEPTUS_VARMATTE_H