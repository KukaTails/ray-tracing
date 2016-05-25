#ifndef LEPTUS_CORE_MATERIAL_H
#define LEPTUS_CORE_MATERIAL_H
#include <memory>

#include "core/color.h"

namespace leptus {

class ShadeRecord;

class Material {
public:
  typedef std::shared_ptr<Material> MaterialPtr;

public:
  virtual Color Shade(const ShadeRecord& shade_recode) const = 0;
  virtual ~Material() = default;
  //virtual Color AreaLightShade(const ShadeRecord& shade_recode) const = 0;
  //virtual Color PathShade(const ShadeRecord& shade_record) const = 0;
};

typedef Material::MaterialPtr MaterialPtr;

} // namespace leptus

#endif // LEPTUS_CORE_MATERIAL_H