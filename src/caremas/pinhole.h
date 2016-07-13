#ifndef LEPTUS_PINHOLE_H
#define LEPTUS_PINHOLE_H

#include "core/camera.h"
#include "core/leptus.h"
#include "core/ray.h"
#include "geometry/geometry.h"

namespace leptus {

class PinHoleCamera : public Camera {
private:
  Float d_;
  Float zoom_;

public:
  PinHoleCamera(Float d = 1);
  PinHoleCamera(Float d,
                const Point3f& eye,
                const Point3f& lookat,
                const Vector3f& up = Vector3f(0.0, 1.1, 0.0));
  virtual std::vector<Ray> GenerateRay(const Point2f& sample) const override;
};

}  // namespace leptus

#endif // LEPTUS_PINTHOLE_H