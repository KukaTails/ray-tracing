#ifndef LEPTUS_RECTANGLE_H
#define LEPTUS_RECTANGLE_H

#include "core/surface.h"
#include "geometry/geometry.h"

namespace leptus {

class Rectangle : public Surface {
public:
  Point3f p_;
  Vector3f a_, b_;
  Normal3f n_;

public:
  Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const Color& color);
  Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const MaterialPtr& material);
  Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const Normal3f& n, const MaterialPtr& material);
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const override;
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;
};

} // namespace leptus

#endif // LEPTUS_RECTANGLE_H