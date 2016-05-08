#ifndef LEPTUS_COMPOUND_H
#define LEPTUS_COMPOUND_H
#include <vector>

#include "core/ray.h"
#include "core/surface.h"

namespace leptus {

class CompoundSurface : public Surface {
protected:
  std::vector<SurPtr> surfaces_;

public:
  CompoundSurface(const std::vector<SurPtr>& surfaces);
  void AddSurface(const SurPtr& surface);
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;
};

} // namespace leptus

#endif // LEPTUS_COMPOUND_H