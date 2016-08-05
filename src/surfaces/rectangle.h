#ifndef LEPTUS_SURFACE_RECTANGLE_H
#define LEPTUS_SURFACE_RECTANGLE_H
#include "core/surface.h"
#include "geometry/geometry.h"

namespace leptus {

class Rectangle : public Surface {
public:
  Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const Color& color);
  Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const MaterialPtr& material);
  Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const Normal3f& n, const MaterialPtr& material);
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;
  virtual BoundingBoxPtr GetBoundingBox( ) const override;
  virtual Point3f Sample( ) const override;
  virtual Normal3f GetNormal(const Point3f& point) const override;
  virtual Float ProbabilityDensityFunc(const HitRecord& hit_rec) const override;

private:
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const override;

private:
  Point3f p_;
  Vector3f a_, b_;
  Normal3f n_;
  Float pdf_;
};

} // namespace leptus

#endif // LEPTUS_SURFACE_RECTANGLE_H