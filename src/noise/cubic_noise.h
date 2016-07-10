#ifndef LEPTUS_NOISE_CUBICNOISE_H
#define LEPTUS_NOISE_CUBICNOISE_H

#include "core/lattice_noise.h"

namespace leptus {

class CubicNoise : public LatticeNoise {
public:
  explicit CubicNoise(unsigned int octave_num = 4, Float lacunarity = 2.0, Float gain = 0.5);
  virtual Float NoiseValue(const Point3f& point) const override;
};

} // namespace leptus

#endif // !LEPTUS_NOISE_CUBICNOISE_H
