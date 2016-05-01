#ifndef LEPTUS_PERSPECTIVE_H
#define LEPTUS_PERSPECTIVE_H

#include "core/ray.h"
#include "core/camera.h"
#include "geometry/vec.h"
#include "geometry/point.h"

namespace leptus {

class PerspectiveCamera : public Camera {
private:
  unsigned fov_;
public:
  PerspectiveCamera(unsigned fov = 30);
  PerspectiveCamera(const ViewPlane& view_plane,
                    unsigned fov = 30);
  PerspectiveCamera(const Point3f& eye,
                    const Point3f& lookat,
                    const Vector3f& up = Vector3f(0.0, 1.0, 0.0));
  virtual Ray GenerateRay(const CameraSample& sample) const override;
};

} // namespace leptus

#endif // LEPTUS_PERSPECTIVE_H