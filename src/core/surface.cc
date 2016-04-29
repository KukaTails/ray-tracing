#include "core/surface.h"

#include "core/color.h"
#include "materials/matte.h"

namespace leptus {

Surface::Surface(const Color& color)
  :material_(std::make_shared<Matte>(color))
{}

Surface::Surface(const MaterialPtr& material)
  : material_(material)
{}

} // namespace leptus