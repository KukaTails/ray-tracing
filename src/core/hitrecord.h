#ifndef LEPTUS_CORE_HIT_RECORD_H 
#define LEPTUS_CORE_HIT_RECORD_H
#include "geometry/geometry.h"

namespace leptus {

struct HitRecord {
  Point3f p_hit_;
  Normal3f n_hit_;
  Point3f local_p_hit_;
  Point2f p_texture_;
  int depth_;

  HitRecord( ) : p_hit_( ), n_hit_( ), local_p_hit_( ), depth_(0) { }
};

} // namespace leptus

#endif // LEPTUS_CORE_HIT_RECORD_H