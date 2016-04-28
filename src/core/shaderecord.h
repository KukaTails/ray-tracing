#ifndef LEPTUS_SHADE_RECORD_H
#define LEPTUS_SHADE_RECORD_H
#include <memory>

#include "core/color.h"
#include "core/material.h"
#include "core/ray.h"
#include "geometry/normal.h"
#include "geometry/point.h"
#include "geometry/vec.h"

namespace leptus {

class World;

class ShadeRecord {
public:
  bool is_hit_;              // if the ray hit a surface
  Point3f p_hit_;            // world coordinates of hit point
  Normal3f n_hit_;           // normal at hit point

  Point3f local_hit_point_;  // local coordinate system used to get texture
  Ray ray_;                  // used to calculate specular highlights
  Vector3f dir_;             // used to calculate area lights
  int depth_;                 // recursion depth
  Color color_;              // used to record the result color
  MaterialPtr material_;     // nearest object's material
  const World& world_;       // reference to world

public:
  ShadeRecord(const World& world);
};

} // namespace leptus

#endif // LEPTUS_SHADE_RECORD_H