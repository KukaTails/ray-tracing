#ifndef LEPTUS_CAMERA_H
#define LEPTUS_CAMERA_H
#include <memory>

#include "core/ray.h"
#include "core/viewplane.h"
#include "geometry/point.h"
#include "geometry/vec.h"

namespace leptus {

struct CameraSample {
  Point2f p_coord_;
};

class Camera {
protected:
  Point3f eye_;
  Point3f lookat_;
  Vector3f up_;
  Vector3f u_, v_, w_;
  float exposure_time_;

public:
  ViewPlane view_plane_;

private:
  void ComputeUVW();

public:
  Camera();
  Camera(const ViewPlane& view_plane);
  Camera(const Point3f& eye,
         const Point3f& lookat,
         const Vector3f& up = Vector3f(0.0, 1.0, 0.0));
  virtual ~Camera() = default;
  virtual Ray GenerateRay(const CameraSample& sample) const = 0;

  Vector2f view_plane_size() const;
};

typedef std::shared_ptr<Camera> CameraPtr;

} // namespace leptus

#endif // LEPTUS_CAMERA_H