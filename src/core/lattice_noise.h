#ifndef LEPTUS_NOISE_LATTICENOISE_H
#define LEPTUS_NOISE_LATTICENOISE_H

#include <memory>
#include "core/leptus.h"
#include "geometry/geometry.h"

namespace leptus {

class LatticeNoise {
public:
  using LatticeNoisePtr = std::shared_ptr<LatticeNoise>;

public:
  explicit LatticeNoise(unsigned int octave_num = 4, Float lacunarity = 2.0, Float gain = 0.5);
  Float FractalSumValue(const Point3f& point) const;
  Float TurbulenceValue(const Point3f& point) const;
  Float FractalBrownianMotionValue(const Point3f& point) const;

  unsigned int octave_num( ) const;
  Float lacunarity( ) const;
  Float gain( ) const;
  
  void SetOctaveNum(unsigned int value);
  void SetLacunarity(Float lacunarity);
  void SetGain(Float gain);

  virtual Float NoiseValue(const Point3f& point) const = 0;

private:
  void InitValueTable( );
  void UpdateMaxMinFractalSumValue( );
  void UpdateMaxMinFractalBrownianMotionValue( );

public:
  static unsigned int table_size( );

protected:
  static unsigned Index(int x, int y, int z);

private:
  static Float RandFloat( );
  static void InitPermutationTable( );
  static unsigned int Perm(int x);

private:
  unsigned int octave_num_;
  Float lacunarity_, gain_;
  Float fractal_sum_min_, fractal_sum_max_;
  Float fractal_brownian_motion_value_min_, fractal_brownian_motion_value_max_;

private:
  static const int TABLE_SIZE = 256;
  static const int TABLE_MASK = TABLE_SIZE - 1;
  static unsigned int PERMUTATION_TABLE[TABLE_SIZE];

protected:
  Float value_table_[TABLE_SIZE];
};

using LatticeNoisePtr = LatticeNoise::LatticeNoisePtr;

} // namespace leptus

#endif // LEPTUS_NOISE_LATTICENOISE_H