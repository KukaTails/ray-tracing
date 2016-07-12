#include "caremas/thinlens.h"
#include "samplers/jitter.h"

namespace leptus {

ThinLens::ThinLens(Float focal_plane_dis, unsigned fov /* = 45 */, Float view_plane_dis /* = 1.0 */, Float lens_radius /* = 4.0 */)
  : Camera(), focal_plane_dis_(focal_plane_dis), fov_(fov), view_plane_dis_(view_plane_dis), lens_radius_(lens_radius),
  zoom_factor_(1.0), sampler_(std::make_shared<JitterSampler>(9, 1))
{ }

void ThinLens::SetLensRadius(Float radius)
{
  Assert(radius > 0.0);
  lens_radius_ = radius;
}

void ThinLens::SetFocalPlaneDistance(Float focal_plane_distance)
{
  Assert(focal_plane_distance > 0.0);
  focal_plane_dis_ = focal_plane_distance;
}

void ThinLens::SetViewPlaneDistance(Float view_plane_distance)
{
  Assert(view_plane_distance > 0.0);
  view_plane_dis_ = view_plane_distance;
}

void ThinLens::SetSampler(const SamplerPtr& sampler)
{
  Assert(sampler != nullptr);
  sampler_ = sampler;
}

void ThinLens::SetZoomFactor(Float zoom_factor)
{
  Assert(zoom_factor > 0.0);
  zoom_factor_ = zoom_factor;
}

Vector3f ThinLens::GetRayDir(const Point2f& pixel_point, const Point2f& lens_point) const
{
  Point2f p;
  p.x_ = pixel_point.x_ * focal_plane_dis_ / view_plane_dis_;
  p.y_ = pixel_point.y_ * focal_plane_dis_ / view_plane_dis_;

  Vector3f dir = (p.x_ - lens_point.x_) * u_ + (p.y_ - lens_point.y_) * v_ - focal_plane_dis_ * w_;
  return Normalize(dir);
}

std::vector<Ray> ThinLens::GenerateRay(const Point2f& point) const
{
  Float pixel_x_size = view_plane_.pix_x_size_;
  Float pixel_y_size = view_plane_.pix_y_size_;
  Float aspect = static_cast<Float>(view_plane_.h_res_) / static_cast<Float>(view_plane_.v_res_);
  Float angle = tan(M_PI * 0.5 * fov_ / 180.0);
  Float x = (2 * ((point.x_ + 0.5) * pixel_x_size) - 1) * angle * aspect;
  Float y = (1 - 2 * ((point.y_ + 0.5) * pixel_y_size)) * angle;

  std::vector<Ray> rays;
  for (int i = 0; i < sampler_->num_samples( ); ++i) {
    Point2f lens_point = sampler_->SampleUnitDisk( ) * lens_radius_;
    Vector3f dir = GetRayDir(Point2f(x, y), lens_point);
    rays.push_back(Ray(Point3f(lens_point.x_, lens_point.y_, eye_.z_), dir));
  }
  return rays;
}

} // namespace leptus