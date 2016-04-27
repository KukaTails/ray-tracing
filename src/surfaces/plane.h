#ifndef LEPTUS_PLANE_H
#define LEPTUS_PLANE_H

#include "core/color.h"
#include "core/surface.h"
#include "core/shaderecord.h"

namespace leptus {

class Plane : public Surface {
public:
  static const Float EPSILON;

public:
  Point3f p_;
  Normal3f n_;

public:
  Plane(const Point3f& p, const Normal3f& n, const Color& color = BLACK);
  Plane(const Point3f& p, const Normal3f& n, const MaterialPtr& material);
  virtual bool Hit(const Ray& ray, Float& t_hit, ShadeRecord& shade_rec) const override;
};

} // namespace leptus

#endif // LEPTUS_PLANE_H 