#ifndef LEPTUS_CORE_LIGHT_H
#define LEPTUS_CORE_LIGHT_H
#include <memory>
#include <vector>

#include "core/color.h"
#include "core/surface.h"
#include "core/hitrecord.h"
#include "geometry/geometry.h"

namespace leptus {

class Light {
public:
  typedef std::shared_ptr<Light> LightPtr;

public:
  Light( ) : cast_shadows_(true) { }
  explicit Light(bool cast_shadows) : cast_shadows_(cast_shadows) { }
  virtual ~Light() = default;
  virtual Color light(const ShadeRecord& shader_rec) const = 0;
  virtual Vector3f GetShadowRayDir(const HitRecord& hit_rec) const = 0;
  virtual bool InShadow(const Point3f& point, const std::vector<SurPtr>& objects) const = 0;
  virtual Float GeometricFactor(const HitRecord& hit_rec) const { return 1.0; }
  virtual Float ProbabilityDensityFunction(const HitRecord& hit_rec) const { return 1.0; }
  
  bool CastShadows( ) const { return cast_shadows_; }
  void SetCastShadows(bool setting) { cast_shadows_ = setting; }

protected:
  bool cast_shadows_;
};

typedef Light::LightPtr LightPtr;

} // namespace leptus

#endif // LEPTUS_CORE_LIGHT_H