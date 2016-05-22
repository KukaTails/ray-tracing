#ifndef LEPTUS_TRANSPARENT_H
#define LEPTUS_TRANSPARENT_H

#include "core/color.h"
#include "core/shaderecord.h"
#include "materials/phong.h"
#include "funcs/specular.h"
#include "funcs/transmitter.h"

namespace leptus {

class Transparent : public Phong {
private:
  PerfectSpecular reflective_func_;
  PerfectTransmitter transmitter_func_;
public:
  Transparent(const Color& color, Float refractive_index,
              Float k_transmit = 0.6, Float k_refl = 0.3,
              Float k_specular = 0.5, Float exp = 200,
              Float k_diffuse = 0.4, Float k_ambient = 0.3);
  Transparent(const Phong& phong, const PerfectSpecular& reflective_func, const PerfectTransmitter& perfect_transmitter);
  virtual Color Shade(const ShadeRecord& shade_rec) const;
};



} // namespace leptus

#endif // LEPTUS_TRANSPARENT_H