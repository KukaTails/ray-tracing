#ifndef LEPTUS_CAMERAS_THINLENS_H
#define LEPTUS_CAMERAS_THINLENS_H
#include "core/leptus.h"
#include "core/camera.h"
#include "core/sampler.h"
#include "geometry/geometry.h"

namespace leptus {

class ThinLens : public Camera {
public:
  ThinLens(Float focal_plane_dis, unsigned fov = 45, Float view_plane_dis = 1.0, Float lens_radius = 4.0);
  
  void SetFocalPlaneDistance(Float focal_plane_distance);
  void SetViewPlaneDistance(Float view_plane_distance);
  void SetLensRadius(Float radius);
  void SetZoomFactor(Float zoom_factor);
  void SetSampler(const SamplerPtr& sampler);
  virtual std::vector<Ray> GenerateRay(const Point2f& point) const override;

private:
  Vector3f GetRayDir(const Point2f& pixel_point, const Point2f& lens_point) const;
  
private:
  Float focal_plane_dis_;
  unsigned fov_;
  Float view_plane_dis_;
  Float lens_radius_;
  Float zoom_factor_;
  SamplerPtr sampler_;
};

} // namespace leptus

#endif // LEPTUS_CAMERAS_THINLENS_H