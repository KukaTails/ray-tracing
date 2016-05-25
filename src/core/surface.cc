#include "core/surface.h"

#include "core/color.h"
#include "materials/matte.h"

namespace leptus {

const Float Surface::EPSILON = 1e-4;

Surface::Surface(const Color& color)
  :material_(std::make_shared<Matte>(color))
{}

Surface::Surface(const MaterialPtr& material)
  : material_(material)
{}

} // namespace leptus