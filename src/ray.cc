#include "ray.h"

namespace raytracing {

Ray::Ray(const glm::vec3& origin, const glm::vec3& dir) :
  origin_(origin), direction_(dir)
{
  direction_ /= glm::length(direction_);
}

glm::vec3 Ray::origin() const { return origin_; }
glm::vec3 Ray::direction() const { return direction_; }

} // namespace raytracing