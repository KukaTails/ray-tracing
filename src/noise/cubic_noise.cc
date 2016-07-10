#include "noise/cubic_noise.h"
#include "geometry/geometry.h"

namespace leptus {

CubicNoise::CubicNoise(unsigned int octave_num /* = 4 */ , Float lacunarity /* = 2.0 */, Float gain /*= 0.5 */)
  : LatticeNoise(octave_num, lacunarity, gain)
{ }

Float CubicNoise::NoiseValue(const Point3f& point) const
{
  Float ix = std::floor(point.x_), fx = point.x_ - ix;
  Float iy = std::floor(point.y_), fy = point.y_ - iy;
  Float iz = std::floor(point.z_), fz = point.z_ - iz;

  Float xknots[4], yknots[4], zknots[4];
  for (int k = -1; k <= 2; ++k) {
    for (int j = -1; j <= 2; ++j) {
      for (int i = -1; i <= 2; ++i) {
        xknots[i + 1] = value_table_[Index(ix + i, iy + j, iz + k)];
      }
      yknots[j + 1] = FourKnotSpline(fx, xknots);
    }
    zknots[k + 1] = FourKnotSpline(fy, yknots);
  }
  return FourKnotSpline(fz, zknots);
}


} // namespace leptus