#include "caremas/perspective.h"

#include <cmath>

namespace leptus {

PerspectiveCamera::PerspectiveCamera(unsigned fov)
  : fov_(fov)
{}

PerspectiveCamera::PerspectiveCamera(const ViewPlane& view_plane, unsigned fov)
  :Camera(view_plane), fov_(fov)
{}

PerspectiveCamera::PerspectiveCamera(const Point3f& eye,
                                     const Point3f& lookat,
                                     const Vector3f& up)
  :Camera(eye, lookat, up)
{}

std::vector<Ray> PerspectiveCamera::GenerateRay(const Point2f& point) const
{
  Float x_size = view_plane_.pix_x_size_;
  Float y_size = view_plane_.pix_y_size_;
  Float aspect = static_cast<Float>(view_plane_.h_res_) / static_cast<Float>(view_plane_.v_res_);
  Float angle = tan(M_PI * 0.5 * fov_ / 180.0);

  Float x = (2 * ((point.x_ + 0.5) * x_size) - 1) * angle * aspect;
  Float y = (1 - 2 * ((point.y_ + 0.5) * y_size)) * angle;
  return {Ray(eye_, Normalize(x * u_ + y * v_ + w_ * -1))};
}

} // namespace leptus