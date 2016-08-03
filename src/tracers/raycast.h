#ifndef LEPTUS_TRACERS_RAY_CAST_H
#define LEPTUS_TRACERS_RAY_CAST_H
#include <memory>

#include "core/color.h"
#include "core/tracer.h"

namespace leptus {

class RayCast : public Tracer {
public:
  RayCast() = default;
  virtual Color TraceRay(const World& world, const Ray& ray) const override;
  virtual Color TraceRay(const World& world, const Ray& ray, const int depth) const override;
  virtual Color TraceRay(const World& world, const Ray& ray, const int depth, int& count, int& jump) const;
};

} // namespace leptus

#endif // LEPTUS_TRACERS_RAY_CAST_H