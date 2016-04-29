#ifndef LEPTUS_SHADE_FUNCS_H
#define LEPTUS_SHADE_FUNCS_H

#include "core/color.h"
#include "core/hitrecord.h"
#include "geometry/vec.h"

namespace leptus {

class Func {
public:
  virtual Color Rho(const HitRecord& hit_rec, const Vector3f& out_dir) const = 0;
  virtual Color F(const HitRecord& hit_rec,
                  const Vector3f& in_dir,
                  const Vector3f& out_dir) const = 0;
  virtual Color SampleF(const HitRecord& hit_rec, Vector3f& in_dir, const Vector3f& out_dir) const = 0;
  virtual ~Func() = default;
};

} // namespace leptus

#endif // LEPTUS_SHADE_FUNCS_H