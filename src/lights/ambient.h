#ifndef LEPTUS_AMBIENT_H
#define LEPTUS_AMBIENT_H

#include "core/light.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class Ambient : public Light {
private:
  Color color_;
  Float light_scale_;

public:
  Ambient();
  Ambient(Color color, Float light_scale = static_cast<Float>(1.0));
  Ambient(Float light_scale, Color color = WHITE);
  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const override;
  virtual Color light(const HitRecord& hit_rec) const override;
  virtual bool CastShadows() const override;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const override;
};

} // namespace leptus

#endif // LEPTUS_AMBIENT_H