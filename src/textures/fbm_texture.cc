#include "textures/fbm_texture.h"

namespace leptus {

FractalBrownianMotionTexture::FractalBrownianMotionTexture(const Color& color, const LatticeNoisePtr& noise_generator /* = std::make_shared<CubicNoise>( ) */)
  : color_(color), min_value_(0.0), max_value_(1.0), noise_generator_(noise_generator)
{}

FractalBrownianMotionTexture::FractalBrownianMotionTexture(const Color& color, unsigned int octave_num, Float lacunarity, Float gain)
  : color_(color), min_value_(0.0), max_value_(1.0), noise_generator_(std::make_shared<CubicNoise>(octave_num, lacunarity, gain))
{ }

FractalBrownianMotionTexture::FractalBrownianMotionTexture(const Color& color, Float min_value, Float max_value)
  : color_(color), min_value_(min_value), max_value_(max_value)
{ }

FractalBrownianMotionTexture::FractalBrownianMotionTexture(const Color& color, Float min_value, Float max_value, unsigned int octave_num, Float lacunarity, Float gain)
  : color_(color), min_value_(min_value), max_value_(max_value), noise_generator_(std::make_shared<CubicNoise>(octave_num, lacunarity, gain))
{ }

Float FractalBrownianMotionTexture::gain( ) const { return noise_generator_->gain( ); }
Float FractalBrownianMotionTexture::lacunarity( ) const { return noise_generator_->gain( ); }
Float FractalBrownianMotionTexture::octave_num( ) const { return noise_generator_->gain( ); }
Float FractalBrownianMotionTexture::min_value( ) const { return min_value_; }
Float FractalBrownianMotionTexture::max_value( ) const { return max_value_; }

void FractalBrownianMotionTexture::SetGain(Float gain) { noise_generator_->SetGain(gain); }
void FractalBrownianMotionTexture::SetLacunarity(Float lacunarity) { noise_generator_->SetLacunarity(lacunarity); }
void FractalBrownianMotionTexture::SetOctaveNum(unsigned int octave_num) { noise_generator_->SetOctaveNum(octave_num); }
void FractalBrownianMotionTexture::SetMinValue(Float min_value) { min_value_ = min_value; }
void FractalBrownianMotionTexture::SetMaxValue(Float max_value) { max_value_ = max_value; }

Color FractalBrownianMotionTexture::GetColor(const HitRecord& hit_rec) const
{
  Float value = noise_generator_->FractalBrownianMotionValue(hit_rec.local_p_hit_);
  value = min_value_ + (max_value_ - min_value_) * value;
  return value * color_;
}

} // namespace leptus