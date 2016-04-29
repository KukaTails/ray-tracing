#ifndef LEPTUS_POINT_LIGHT_H
#define LEPTUS_POINT_LIGHT_H

#include "core/color.h"
#include "core/leptus.h"
#include "core/light.h"
#include "core/shaderecord.h"
#include "geometry/point.h"

namespace leptus {

class PointLight : public Light {
private:
  Point3f location_;
  Color color_;
  Float light_scale_;

public:
  PointLight(const Point3f& location);
  PointLight(const Point3f& location, Float ligth_scale, Color color = WHITE);
  PointLight(const Point3f& location, Color color, Float ligth_scale = static_cast<Float>(1.0));

  virtual Color light() const override;
  virtual bool CastShadows() const override;
  virtual bool InShadow(const Point3f& point,const std::vector<SurPtr>& objects) const override;
  virtual Vector3f GetShadowRayDir(const ShadeRecord& shade_rec) const override;
};

} // namespace leptus

#endif // LEPTUS_POINT_LIGHT_H