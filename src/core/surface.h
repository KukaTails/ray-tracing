#ifndef LEPTUS_SURFACE_H
#define LEPTUS_SURFACE_H
#include <memory>

#include "core/color.h"
#include "core/leptus.h"
#include "core/material.h"
#include "core/shaderecord.h"

namespace leptus {

class Surface {
public:
  typedef std::shared_ptr<Surface> SurPtr;

private:
  MaterialPtr material_;

public:
  Surface(const Color& color = Color(0.5, 0.5, 0.5));
  Surface(const MaterialPtr& material);
  virtual ~Surface() = default;

  MaterialPtr material() const { return material_; }
  virtual bool ShadowHit(const Ray& ray, Float &t_hit) const = 0;
  virtual bool Hit(const Ray& ray, Float& t_hit, ShadeRecord& shade_rec) const = 0;
};

typedef Surface::SurPtr SurPtr;

} // namespace leptus

#endif // LEPTUS_SURFACE_H