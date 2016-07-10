#include "core/lattice_noise.h"
#include <algorithm>

namespace leptus {

unsigned int LatticeNoise::PERMUTATION_TABLE[TABLE_SIZE];

LatticeNoise::LatticeNoise(unsigned int octave_num /* = 4 */, Float lacunarity /* = 2.0 */, Float gain /* = 0.5 */)
  : octave_num_(octave_num), lacunarity_(lacunarity), gain_(gain)
{
  InitValueTable();
  InitPermutationTable( );
  UpdateMaxMinFractalSumValue( );
  UpdateMaxMinFractalBrownianMotionValue( );
}

Float LatticeNoise::RandFloat( )
{
  const int range = 1000;
  return static_cast<Float>(rand( ) % 1000) / 1000.0;
}

void LatticeNoise::InitValueTable()
{
  for (int i = 0; i < TABLE_SIZE; ++i)
    value_table_[i] = 1.0 - 2.0 * RandFloat( );
}

void LatticeNoise::UpdateMaxMinFractalSumValue( )
{
  fractal_brownian_motion_value_max_ = (1 - std::pow(gain_, octave_num_ - 1)) / (1 - gain_);
  fractal_brownian_motion_value_min_ = -fractal_brownian_motion_value_max_;
}

void LatticeNoise::UpdateMaxMinFractalBrownianMotionValue( )
{
  fractal_sum_max_ = 2.0 * (1 - std::pow(0.5, octave_num_ - 1));
  fractal_sum_min_ = -fractal_sum_max_;
}

void LatticeNoise::InitPermutationTable( )
{
  static bool is_initialized = false;

  if (!is_initialized) {
    for (int i = 0; i < TABLE_SIZE; ++i)
      PERMUTATION_TABLE[i] = i;
    std::random_shuffle(PERMUTATION_TABLE, PERMUTATION_TABLE + TABLE_SIZE);
    is_initialized = true;
  }
}

unsigned int LatticeNoise::Perm(int x)
{
  return PERMUTATION_TABLE[x & TABLE_MASK];
}

unsigned LatticeNoise::Index(int x, int y, int z)
{
  return Perm(x + Perm(y + Perm(z)));
}

Float LatticeNoise::FractalSumValue(const Point3f& point) const
{
  Float amplitude = 1.0;
  Float frequency = 1.0;
  Float fractal_sum = 0.0;

  for (int i = 0; i < octave_num_; ++i) {
    fractal_sum += amplitude * NoiseValue(frequency * point);
    amplitude *= 0.5;
    frequency *= 2.0;
  }
  fractal_sum = (fractal_sum - fractal_sum_min_) / (fractal_sum_max_ - fractal_sum_min_);
  return fractal_sum;
}


Float LatticeNoise::TurbulenceValue(const Point3f& point) const
{
  Float amplitude = 1.0;
  Float frequency = 1.0;
  Float turbulence = 0.0;

  for (int i = 0; i < octave_num_; ++i) {
    turbulence += amplitude * std::abs(NoiseValue(frequency * point));
    amplitude *= 0.5;
    frequency *= 2.0;
  }
  turbulence /= fractal_sum_max_;
  return turbulence;
}

Float LatticeNoise::FractalBrownianMotionValue(const Point3f& p) const
{
  double amplitude = 1.0;
  double frequency = 1.0;
  double fractal_brown_motion_value = 0.0;

  for (int i = 0; i < octave_num_; ++i) {
    fractal_brown_motion_value += amplitude * NoiseValue(frequency * p);
    amplitude *= gain_;
    frequency *= lacunarity_;
  }
  return (fractal_brown_motion_value - fractal_brownian_motion_value_min_) / (fractal_brownian_motion_value_max_ - fractal_brownian_motion_value_min_);
}

unsigned int LatticeNoise::table_size( )
{
  return TABLE_SIZE;
}

unsigned int LatticeNoise::octave_num( ) const { return octave_num_; }
Float LatticeNoise::lacunarity( ) const { return lacunarity_; }
Float LatticeNoise::gain( ) const { return gain_; }

void LatticeNoise::SetOctaveNum(unsigned int value)
{
  octave_num_ = value;
  UpdateMaxMinFractalSumValue( );
  UpdateMaxMinFractalBrownianMotionValue( );
}

void LatticeNoise::SetLacunarity(Float lacunarity)
{
  lacunarity_ = lacunarity;
  UpdateMaxMinFractalBrownianMotionValue( );
}

void LatticeNoise::SetGain(Float gain)
{
  gain_ = gain;
  UpdateMaxMinFractalBrownianMotionValue( );
}

} // namespace leptus