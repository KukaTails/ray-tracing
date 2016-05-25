#include "core/color.h"

namespace leptus {

Color::Color() : r_(0), g_(0), b_(0) {}
Color::Color(Float c) : r_(c), g_(c), b_(c) {}
Color::Color(Float r, Float g, Float b)
  : r_(r), g_(g), b_(b)
{}

const Color Color::operator+(const Color& color) const
{
  return Color(r_ + color.r_, g_ + color.g_, b_ + color.b_);
}

const Color operator*(Float scale, const Color& color)
{
  return Color(color.r_ * scale, color.g_ * scale, color.b_ * scale);
}

const Color operator*(const Color& color, Float scale)
{
  return scale * color;
}

const Color& Color::operator+=(const Color& color)
{
  r_ += color.r_;
  g_ += color.g_;
  b_ += color.b_;
  return *this;
}

const Color Color::operator*(const Color& color) const
{
  return Color(r_ * color.r_, g_ * color.g_, b_ * color.b_);
}

std::ostream& operator<<(std::ostream& os, const Color& color)
{
  os << "[r=" << color.r_ << ", g=" << color.g_ << ", b=" << color.b_ << "]";
  return os;
}

} // namespace leptus