#ifndef LEPTUS_DISK_H
#define LEPTUS_DISK_H

#include "core/leptus.h"
#include "core/ray.h"
#include "core/surface.h"
#include "core/hitrecord.h"
#include "geometry/point.h"
#include "geometry/normal.h"

namespace leptus {

class Disk : public Surface {
public:
  static const Float EPSILON;

private:
  Point3f center_;
  Float radius_;
  Normal3f n_;

public:
  Disk(const Point3f& center, Float radius, const Normal3f& n);
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
};


} // namespace leptus


#endif // LEPTUS_DISK_H