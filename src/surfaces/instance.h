#ifndef LEPTUS_INSTANCE_H
#define LEPTUS_INSTANCE_H

#include <memory>
#include "core/surface.h"
#include "geometry/transform.h"

namespace leptus {

class Instance : public Surface {
public:
  using InstancePtr = std::shared_ptr<Instance>;

public:
  Instance(const SurPtr& surface);
  void TransformTexture(bool option);
  void Translate(Float x, Float y, Float z);
  void Scale(Float x, Float y, Float z);
  void RotateX(Float radians);
  void RotateY(Float radians);
  void RotateZ(Float radians);
  void Rotate(Float x_radians, Float y_radians, Float z_radians);

  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;

private:
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const;

private:
  SurPtr surface_;
  Transform transform_;
  bool is_texture_transformed_;
};

using InstancePtr = Instance::InstancePtr;

} // namespace leptus

#endif // LEPTUS_INSTANCE_H