#ifndef LEPTUS_MATERIAL_EMISSIVE_H
#define LEPTUS_MATERIAL_EMISSIVE_H
#include "core/color.h"
#include "core/hitrecord.h"
#include "core/leptus.h"
#include "core/material.h"

namespace leptus {

class Emissive : public Material {
public:
  explicit Emissive(const Color& color, Float ls = 0.5f);
  
  void setColor(const Color& color);
  void scaleRadiance(Float scaling_factor);
  Color light(const HitRecord& hit_rec) const;

  virtual Color Shade(const ShadeRecord& shade_rec) const override;
  virtual Color AreaLightShade(const ShadeRecord& shade_rec) const override;

private:
  Color color_;
  Float ls_;
};

} // namespace leptus

#endif // LEPTUS_MATERIAL_EMISSIVE_H