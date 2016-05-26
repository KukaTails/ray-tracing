#ifndef LEPTUS_TRANSMITTER_H
#define LEPTUS_TRANSMITTER_H

#include "core/color.h"
#include "core/hitrecord.h"
#include "core/leptus.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class PerfectTransmitter {
private:
  Float refractive_index_;
  Float k_transmit_;
public:
  PerfectTransmitter(Float refractive_index, Float k_transmit);
  bool TotalInternalReflection(const Ray& ray, const HitRecord& hit_rec) const;
  Color SampleF(const HitRecord& hit_rec, const Vector3f& out_dir, Vector3f& refractive_dir) const;
};


} // namespace leptus

#endif // LEPTUS_TRANSMITTER_H