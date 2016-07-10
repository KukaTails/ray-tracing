#include "turbulence_texture.h"

namespace leptus {

TurbulenceTexture::TurbulenceTexture(const Color& color, const LatticeNoisePtr& noise_generator /* = std::make_shared<CubicNoise>( ) */)
  : color_(color), min_value_(0.0), max_value_(1.0), noise_generator_(noise_generator)
{ }

TurbulenceTexture::TurbulenceTexture(const Color& color, Float min_value, Float max_value)
  : color_(color), min_value_(min_value), max_value_(max_value), noise_generator_(std::make_shared<CubicNoise>( ))
{ }

TurbulenceTexture::TurbulenceTexture(const Color& color, unsigned int octave_num)
  : color_(color), min_value_(0.0), max_value_(1.0), noise_generator_(std::make_shared<CubicNoise>(octave_num))
{ }

TurbulenceTexture::TurbulenceTexture(const Color& color, Float min_value, Float max_value, unsigned int octave_num)
  : color_(color), min_value_(min_value), max_value_(max_value), noise_generator_(std::make_shared<CubicNoise>(octave_num))
{ }

Color TurbulenceTexture::GetColor(const HitRecord& hit_rec) const
{
  Float value = noise_generator_->TurbulenceValue(hit_rec.local_p_hit_);
  value = min_value_ + (max_value_ - min_value_) * value;
  return value * color_;
}

Float TurbulenceTexture::min_value( ) const
{
  return min_value_;
}

Float TurbulenceTexture::max_value( ) const
{
  return max_value_;
}

void TurbulenceTexture::SetMinValue(Float min_value)
{
  min_value_ = min_value;
}

void TurbulenceTexture::SetMaxValue(Float max_value)
{
  max_value_ = max_value;
}

void TurbulenceTexture::SetOctaveNum(unsigned int value)
{
  noise_generator_->SetOctaveNum(value);
}

} // namespace leptus