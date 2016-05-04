#ifndef LEPTUS_WHITTED_H
#define LEPTUS_WHITTED_H

#include "core/color.h"
#include "core/tracer.h"

namespace leptus {

class Whitted : public Tracer {
public:
  static const int MAX_DEPTH;
public:
  Whitted( ) = default;
  virtual Color TraceRay(const World& world, const Ray& ray) const override;
  virtual Color TraceRay(const World& world, const Ray& ray, const int depth) const override;
};


} // namespace leptus

#endif // LEPTUS_WHITTED_H