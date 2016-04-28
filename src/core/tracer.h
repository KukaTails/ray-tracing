#ifndef LEPTUS_TRACER_H
#define LEPTUS_TRACER_H
#include <memory>

#include "core/color.h"
#include "core/ray.h"
#include "core/leptus.h"
#include "world/world.h"

namespace leptus {

class World;

class Tracer {
public:
  typedef std::shared_ptr<Tracer> TracerPtr;

public:
  Tracer() = default;
  virtual ~Tracer() = default;

  virtual Color TraceRay(const World& world, const Ray& ray) const = 0;
  virtual Color TraceRay(const World& world, const Ray& ray, const int depth) const = 0;
};

typedef Tracer::TracerPtr TracerPtr;

} // namespace leptus

#endif // LEPTUS_TRECER_H