#ifndef LEPTUS_SPHERE_H
#define LEPTUS_SPHERE_H

#include "core/color.h"
#include "core/surface.h"
#include "core/material.h"
#include "geometry/point.h"

namespace leptus {

class Sphere: public Surface {
public:
  Float radius_;
  Point3f center_;

public:
  Sphere(const Point3f& center, Float radius, const Color& color);
  Sphere(const Point3f& center, Float radius, const MaterialPtr& material);
  virtual bool Hit(const Ray& ray, Float& t_hit, ShadeRecord& shade_rec) const override;
};

} // namespace leptus

#endif // LEPTUS_SPHERE_H
