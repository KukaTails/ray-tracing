#ifndef LEPTUS_CORE_RENDER_H
#define LEPTUS_CORE_RENDER_H

#include "core/camera.h"
#include "core/sampler.h"
#include "core/tracer.h"
#include "caremas/perspective.h"
#include "samplers/regular.h"
#include "tracers/whitted.h"

namespace leptus {

class Render {
private:
  TracerPtr tracer_;
  SamplerPtr sampler_;
  CameraPtr camera_;
  std::shared_ptr<std::vector<Vector3f>> image_;

public:
  Render(TracerPtr tracer = std::make_shared<WhittedTracer>(),
         CameraPtr camera = std::make_shared<PerspectiveCamera>( ),
         SamplerPtr sampler = std::make_shared<RegularSampler>(1, 1));
  void operator()(const WorldPtr& world) const;
  void Save(const std::string& file_path) const;
};

} // namespace leptus

#endif // LEPTUS_CORE_RENDER_H