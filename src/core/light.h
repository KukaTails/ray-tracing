#ifndef LEPTUS_LIGHT_H
#define LEPTUS_LIGHT_H
#include <memory>
#include <vector>

#include "core/color.h"
#include "core/surface.h"
#include "core/shaderecord.h"
#include "core/ray.h"
#include "geometry/point.h"
#include "geometry/vec.h"

namespace leptus {

class Light {
public:
  typedef std::shared_ptr<Light> LightPtr;
protected:
  bool shadows_;
public:
  virtual ~Light() = default;
  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const = 0;
  virtual Color light() const = 0;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const = 0;
  virtual bool CastShadows() const = 0;
};

typedef Light::LightPtr LightPtr;

} // namespace leptus

#endif // LEPTUS_LIGHT_H