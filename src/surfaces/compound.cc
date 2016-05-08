#include "surfaces/compound.h"

#include <limits>

namespace leptus {

CompoundSurface::CompoundSurface(const std::vector<SurPtr>& surfaces)
  : surfaces_(surfaces)
{ }

void CompoundSurface::AddSurface(const SurPtr& surface)
{
  surfaces_.push_back(surface);
}

bool CompoundSurface::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  bool is_hit = false;
  HitRecord tmp_hit_rec;
  Float t_min = std::numeric_limits<Float>::max();

  for (int i = 0; i < surfaces_.size(); ++i) {
    if (surfaces_[i]->Hit(ray, t_hit, tmp_hit_rec) && (t_hit < t_min)) {
      is_hit = true;
      t_min = t_hit;
      material_ = surfaces_[i]->material();
      hit_rec = tmp_hit_rec;
    }
  }
  return is_hit;
}

bool CompoundSurface::ShadowHit(const Ray& ray, Float& t_hit) const
{
  return Hit(ray, t_hit, HitRecord( ));
}

} // namespace leptus