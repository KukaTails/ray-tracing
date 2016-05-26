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
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const override;
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float &t_hit) const override;
};

} // namespace leptus

#endif // LEPTUS_PLANE_H 