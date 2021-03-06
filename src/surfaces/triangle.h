#ifndef LEPTUS_SURFACE_TRIANGLE_H
#define LEPTUS_SURFACE_TRIANGLE_H
#include "core/ray.h"
#include "core/material.h"
#include "core/surface.h"
#include "core/shaderecord.h"
#include "geometry/geometry.h"

namespace leptus {

class Triangle : public Surface {
public:
  Triangle(const Point3f& p0, const Point3f& p1, const Point3f& p2, const Color& color);
  Triangle(const Point3f& p0, const Point3f& p1, const Point3f& p2, const MaterialPtr& material);
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual BoundingBoxPtr GetBoundingBox( ) const override;

private:
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const override;

private:
  Point3f p0_, p1_, p2_;
  Normal3f n_;
};

} // namespace leptus

#endif // LEPTUS_SURFACE_TRIANGLE_H