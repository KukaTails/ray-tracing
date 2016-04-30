#ifndef LEPTUS_COLOR_H
#define LEPTUS_COLOR_H

#include "core/leptus.h"

namespace leptus {

class Color {
public:
  Float r_, g_, b_;

public:
  Color();
  Color(Float c);
  Color(Float r, Float g, Float b);

  friend const Color operator*(Float scale, const Color& color);
  friend const Color operator*(const Color& color, Float scale);

  const Color operator+(const Color& color) const;
  const Color operator*(const Color& color) const;
  const Color& operator+=(const Color& color);
};

const Color BLACK = Color(0.0, 0.0, 0.0);
const Color WHITE = Color(1.0, 1.0, 1.0);
const Color RED = Color(1.0, 0.0, 0.0);
const Color GREEN = Color(0.0, 1.0, 0.0);
const Color BLUE = Color(0.0, 0.0, 1.0);

} // namespace leptus

#endif // LEPTUS_COLOR_H