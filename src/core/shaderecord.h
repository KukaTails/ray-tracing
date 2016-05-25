#ifndef LEPTUS_SHADE_RECORD_H
#define LEPTUS_SHADE_RECORD_H
#include <memory>

#include "core/color.h"
#include "core/hitrecord.h"
#include "core/material.h"
#include "core/ray.h"
#include "core/tracer.h"
#include "core/world.h"
#include "geometry/geometry.h"

namespace leptus {

class ShadeRecord {
public:
  bool is_hit_;                    // if the ray hit a surface
  HitRecord hit_rec_;              // world coordinates of hit point and hit normal
  Point2f p_texture_;              // local coordinate system used to get texture
  Ray ray_;                        // used to calculate specular highlights
  Vector3f dir_;                   // used to calculate area lights
  Color color_;                    // used to record the result color
  MaterialPtr material_;     // nearest object's material
  const World& world_;           // pointer which point to world
  const Tracer& tracer_;               // pointer which point to tracer

public:
  ShadeRecord(const World& world);
  ShadeRecord(const ShadeRecord& shade_rec, const Tracer& tracer);
};

} // namespace leptus

#endif // LEPTUS_SHADE_RECORD_H