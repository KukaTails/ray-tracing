#ifndef LEPTUS_CORE_CAMERA_H
#define LEPTUS_CORE_CAMERA_H
#include <memory>

#include "core/viewplane.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class Camera {
public:
  typedef std::shared_ptr<Camera> CameraPtr;

protected:
  Point3f eye_;
  Point3f lookat_;
  Vector3f up_;
  Vector3f u_, v_, w_;
  float exposure_time_;
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
  virtual Ray GenerateRay(const Point2f& point) const = 0;
  Vector2i view_plane_size() const;
};

typedef Camera::CameraPtr CameraPtr;

} // namespace leptus

#endif // LEPTUS_CORE_CAMERA_H
