#ifndef LEPTUS_SURFACE_H
#define LEPTUS_SURFACE_H
#include <memory>

#include "leptus.h"
#include "geometry.h"
#include "interaction.h"

namespace leptus {

class Surface {
public:
  typedef std::shared_ptr<Surface> SurPtr;

public:
  Surface() = default;
  virtual ~Surface() = default;
  virtual bool Hit(const Ray& ray, Float& t_hit, SurfaceInteraction& isect) const = 0;
};

} // namespace raytracing

#endif // RAY_TRACING_SURFACE_H