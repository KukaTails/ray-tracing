#include "caremas/pinhole.h"

namespace leptus {

PinHoleCamera::PinHoleCamera(Float d)
  :d_(d), Camera()
{}

PinHoleCamera::PinHoleCamera(Float d,
                             const Point3f& eye,
                             const Point3f& lookat,
                             const Vector3f& up)
  :d_(d), Camera(eye, lookat, up)
{}

Ray PinHoleCamera::GenerateRay(const Point2f& sample) const
{
  return Ray();
}

} // namespace leptus