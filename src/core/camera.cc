#include "core/camera.h"
#include "geometry/geometry.h"

namespace leptus {

Camera::Camera()
  :eye_(Point3f(0, 0, -1)), lookat_(Point3f(0, 0, 0)), up_(Vector3f(0, 1, 0))
{
  ComputeUVW();
}

Camera::Camera(const ViewPlane& view_plane) : Camera()
{
  view_plane_ = view_plane;
  ComputeUVW();
}


Camera::Camera(const Point3f& eye, const Point3f& lookat, const Vector3f& up)
  :eye_(eye), lookat_(lookat), up_(up)
{
  ComputeUVW();
}

inline void Camera::ComputeUVW()
{
  w_ = Normalize(eye_ - lookat_);
  u_ = Normalize(Cross(up_, w_));
  v_ = Cross(w_, u_);
}

} // namespace leptus