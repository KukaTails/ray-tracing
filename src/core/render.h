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
  TracerPtr tracer_ = std::make_shared<WhittedTracer>( );
  SamplerPtr sampler_ = std::make_shared<RegularSampler>(1, 1);
  CameraPtr camera_ = std::make_shared<PerspectiveCamera>();
  std::shared_ptr<std::vector<Vector3f>> image_ = std::make_shared<std::vector<Vector3f>>(
    camera_->view_plane_size( ).x_ * camera_->view_plane_size( ).y_);

public:
  Render( ) = default;
  Render(TracerPtr tracer, CameraPtr camera, SamplerPtr sampler);
  void SetCamera(const CameraPtr& camera);
  void operator()(const WorldPtr& world) const;
  void Save(const std::string& file_path) const;
};

} // namespace leptus

#endif // LEPTUS_CORE_RENDER_H