#ifndef LEPTUS_TRACERS_WHITTED_H
#define LEPTUS_TRACERS_WHITTED_H

#include "core/color.h"
#include "core/tracer.h"

namespace leptus {

class WhittedTracer : public Tracer {
public:
  WhittedTracer( ) = default;
  virtual Color TraceRay(const World& world, const Ray& ray) const override;
  virtual Color TraceRay(const World& world, const Ray& ray, const int depth) const override;
};


} // namespace leptus

#endif // LEPTUS_TRACERS_WHITTED_H