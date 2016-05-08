#ifndef LEPTUS_INSTANCE_H
#define LEPTUS_INSTANCE_H

#include "core/surface.h"
#include "geometry/transform.h"

namespace leptus {

class Instance : public Surface {
public:
  Instance(const SurPtr& surface);
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;
private:
  SurPtr surface_;
  Transform transform_;
  bool is_texture_transformed_;
};

} // namespace leptus

#endif // LEPTUS_INSTANCE_H