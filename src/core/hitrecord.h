#ifndef LEPTUS_HIT_RECORD_H 
#define LEPTUS_HIT_RECORD_H

#include "geometry/point.h"
#include "geometry/normal.h"

namespace leptus {

struct HitRecord {
  Point3f p_hit_;
  Normal3f n_hit_;
  Point3f local_p_hit_;
  int depth_;
};


} // namespace leptus

#endif // LEPTUS_HIT_RECORD_H