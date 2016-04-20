#ifndef RAY_TRACING_RAY_H
#define RAY_TRACING_RAY_H

#include "glm/glm.hpp"

namespace raytracing {

class Ray {
private:
  glm::vec3 origin_;
  glm::vec3 direction_;
public:
  Ray(const glm::vec3& origin, const glm::vec3& dir);
  glm::vec3 origin() const;
  glm::vec3 direction() const;
};

} // namespace taytracing

#endif // RAY_TRACING_RAY_H