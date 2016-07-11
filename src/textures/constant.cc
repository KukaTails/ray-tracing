#include "textures/constant.h"

namespace leptus {

ConstantColor::ConstantColor(Float r, Float g, Float b)
  : color_(r, g, b)
{ }

ConstantColor::ConstantColor(const Color& color)
  : color_(color)
{ }

void ConstantColor::SetColor(const Color& color)
{
  color_ = color;
}

Color ConstantColor::GetColor(const HitRecord& hit_rec) const
{
  return color_;
}

} // namespace leptus