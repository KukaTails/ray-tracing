#include "core/color.h"

namespace leptus {

Color::Color() : r_(0), g_(0), b_(0) {}
Color::Color(Float c) : r_(c), g_(c), b_(c) {}
Color::Color(Float r, Float g, Float b)
  : r_(r), g_(g), b_(b)
{}

Color Color::operator+(const Color& color) const
{
  return Color(r_ + color.r_, g_ + color.g_, b_ + color.b_);
}

Color operator*(Float scale, const Color& color)
{
  return Color(color.r_ * scale, color.g_ * scale, color.b_ * scale);
}

Color operator*(const Color& color, Float scale)
{
  return scale * color;
}

Color& Color::operator+=(const Color& color)
{
  r_ += color.r_;
  g_ += color.g_;
  b_ += color.b_;
  return *this;
}

Color Color::operator*(const Color& color) const
{
  return Color(r_ * color.r_, g_ * color.g_, b_ * color.b_);
}

} // namespace leptus