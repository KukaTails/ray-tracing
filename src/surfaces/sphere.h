#ifndef LEPTUS_SPHERE_H
#define LEPTUS_SPHERE_H

#include "core/color.h"
#include "core/hitrecord.h"
#include "core/surface.h"
#include "core/material.h"
#include "geometry/geometry.h"

namespace leptus {

class Sphere: public Surface {
public:
  Float radius_;
  Point3f center_;

private:
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const override;
public:
  Sphere(const Point3f& center, Float radius, const Color& color);
  Sphere(const Point3f& center, Float radius, const MaterialPtr& material);
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;
};

} // namespace leptus

#endif // LEPTUS_SPHERE_H
