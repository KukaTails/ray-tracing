#include "core/render.h"

#include <algorithm>
#include <fstream>

namespace leptus {

Render::Render(TracerPtr tracer /* = std::make_shared<WhittedTracer>() */,
               CameraPtr camera /* = std::make_shared<PerspectiveCamera>( ) */,
               SamplerPtr sampler /* = std::make_shared<RegularSampler>(1, 1) */)
  : tracer_(tracer), sampler_(sampler), camera_(camera),
  image_(std::make_shared<std::vector<Vector3f>>(camera->view_plane_size( ).x_ * camera->view_plane_size( ).y_))
{ }

void Render::SetTracer(const TracerPtr& tracer)
{
  Assert(tracer);
  tracer_ = tracer;
}

void Render::SetCamera(const CameraPtr& camera)
{
  Assert(camera);
  camera_ = camera;
}

void Render::SetSampler(const SamplerPtr& sampler)
{
  Assert(sampler);
  sampler_ = sampler;
}

void Render::operator()(const WorldPtr& world) const
{
  const Vector2i& view_plane_size = camera_->view_plane_size( );
  int progross = -1;

  if (tracer_ != nullptr) {
    sampler_->GenerateSamples( );
    for (unsigned y = 0; y < view_plane_size.y_; ++y) {
      for (unsigned x = 0; x < view_plane_size.x_; ++x) {
        if (static_cast<int>(y * 100 / view_plane_size.y_) > progross) {
          progross++;
          std::cout << "render: %" << progross << std::endl;
        }

        Color color;
        std::vector<Ray> rays;
        for (int i = 0; i < sampler_->num_samples( ); ++i) {
          Point2f bias = sampler_->SampleUnitSquare( );
          rays = camera_->GenerateRay(Point2f(x + bias.x_, y + bias.y_));
          for (auto& ray : rays) {
            color += tracer_->TraceRay(*world, ray);
          }
        }
        color = color * (1.0 / (sampler_->num_samples( ) * rays.size()));
        (*image_)[y * view_plane_size.x_ + x] = Vector3f(std::min(color.r_, 1.0f),
                                                         std::min(color.g_, 1.0f),
                                                         std::min(color.b_, 1.0f));
      }
    }
  }
}

void Render::Save(const std::string& file_path) const
{
  std::ofstream ofs(file_path, std::ios::out | std::ios::binary);
  Vector2i size = camera_->view_plane_size( );
  int h_res = size.x_, v_res = size.y_;

  ofs << "P6\n" << h_res << " " << v_res << "\n255\n";
  for (unsigned i = 0; i < h_res * v_res; ++i) {
    ofs << (unsigned char)(std::min(float(1), (*image_)[i].x_) * 255) <<
      (unsigned char)(std::min(float(1), (*image_)[i].y_) * 255) <<
      (unsigned char)(std::min(float(1), (*image_)[i].z_) * 255);
  }
}

} // namespace leptus