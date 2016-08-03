#ifndef LEPTUS_TRACERS_AREA_LIGHTING_H
#define LEPTUS_TRACERS_AREA_LIGHTING_H
#include "core/tracer.h"

namespace leptus {

class AreaLighting : public Tracer {
public:
  AreaLighting( ) = default;
  virtual Color TraceRay(const World& world, const Ray& ray) const override;
  virtual Color TraceRay(const World& world, const Ray& ray, const int depth) const override;
};

} // namespace leptus

#endif // LEPTUS_TRACERS_AREA_LIGHTING_H