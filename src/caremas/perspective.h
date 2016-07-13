#ifndef LEPTUS_PERSPECTIVE_H
#define LEPTUS_PERSPECTIVE_H

#include "core/ray.h"
#include "core/camera.h"
#include "geometry/geometry.h"

namespace leptus {

class PerspectiveCamera : public Camera {
private:
  unsigned fov_;
public:
  PerspectiveCamera(unsigned fov = 45);
  PerspectiveCamera(const ViewPlane& view_plane,
                    unsigned fov = 30);
  PerspectiveCamera(const Point3f& eye,
                    const Point3f& lookat,
                    const Vector3f& up = Vector3f(0.0, 1.0, 0.0));
  virtual std::vector<Ray> GenerateRay(const Point2f& point) const override;
};

} // namespace leptus

#endif // LEPTUS_PERSPECTIVE_H