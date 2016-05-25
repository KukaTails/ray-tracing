#include "core/camera.h"

namespace leptus {

Camera::Camera()
  :eye_(Point3f(0, 0, 1)), lookat_(Point3f(0, 0, 0)), up_(Vector3f(0, 1, 0))
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
  v_ = Normalize(Cross(w_, u_));
}

Vector2i Camera::view_plane_size() const
{
  return Vector2i(view_plane_.h_res_, view_plane_.v_res_);
}

} // namespace leptus