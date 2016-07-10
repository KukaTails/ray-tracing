#include "noise/linear_noise.h"
#include "geometry/geometry.h"

namespace leptus {

LinearNoise::LinearNoise(unsigned int octave_num /* = 4 */, Float lacunarity /* = 2.0 */, Float gain /* = 0.5 */)
  : LatticeNoise(octave_num, lacunarity, gain)
{ }

Float LinearNoise::NoiseValue(const Point3f& point) const
{
  Float ix = floor(point.x_);
  Float iy = floor(point.y_);
  Float iz = floor(point.z_);
  Float fx = point.x_ - ix;
  Float fy = point.y_ - iy;
  Float fz = point.z_ - iz;
  Float value[2][2][2];

  for (int k = 0; k <= 1; ++k)
    for (int j = 0; j <= 1; ++j)
      for (int i = 0; i <= 1; ++i) {
        value[k][j][i] = value_table_[Index(ix + i, iy + j, iz + k)];
      }

  Float x0 = LinearInterpolation(fx, value[0][0][0], value[0][0][1]);
  Float x1 = LinearInterpolation(fx, value[0][1][0], value[0][1][1]);
  Float x2 = LinearInterpolation(fx, value[1][0][0], value[1][0][1]);
  Float x3 = LinearInterpolation(fx, value[1][1][0], value[1][1][1]);
  Float y0 = LinearInterpolation(fy, x0, x1);
  Float y1 = LinearInterpolation(fy, x2, x3);
  Float z0 = LinearInterpolation(fz, y0, y1);
  return z0;
}

} // namespace leptus