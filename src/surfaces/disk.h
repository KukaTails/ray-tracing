#ifndef LEPTUS_SURFACE_DISK_H
#define LEPTUS_SURFACE_DISK_H
#include "core/leptus.h"
#include "core/ray.h"
#include "core/surface.h"
#include "core/hitrecord.h"
#include "geometry/geometry.h"

namespace leptus {

class Disk : public Surface {
public:
  Disk(const Point3f& center, Float radius, const Normal3f& n, const MaterialPtr& material);
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;

private:
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const override;

private:
  Point3f center_;
  Float radius_;
  Normal3f n_;
};

} // namespace leptus

#endif // LEPTUS_SURFACE_DISK_H