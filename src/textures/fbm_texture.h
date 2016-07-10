#ifndef LEPTUS_TEXTURES_FBM_TEXTURES_H
#define LEPTUS_TEXTURES_FBM_TEXTURES_H
#include <memory>
#include "core/texture.h"
#include "core/lattice_noise.h"
#include "noise/cubic_noise.h"

namespace leptus {

class FractalBrownianMotionTexture : public Texture {
public:
  using FractalBrownianMotionTexturePtr = std::shared_ptr<FractalBrownianMotionTexture>;

public:
  explicit FractalBrownianMotionTexture(const Color& color, const LatticeNoisePtr& noise_generator = std::make_shared<CubicNoise>( ));
  FractalBrownianMotionTexture(const Color& color, unsigned int octave_num, Float lacunarity, Float gain);
  FractalBrownianMotionTexture(const Color& color, Float min_value, Float max_value);
  FractalBrownianMotionTexture(const Color& color, Float min_value, Float max_value, unsigned int octave_num, Float lacunarity, Float gain);
  
  Float gain( ) const;
  Float lacunarity( ) const;
  Float octave_num( ) const;
  void SetGain(Float gain);
  void SetLacunarity(Float lacunarity);
  void SetOctaveNum(unsigned int octave_num);
  Float min_value( ) const;
  Float max_value( ) const;
  void SetMinValue(Float min_value);
  void SetMaxValue(Float max_value);
  virtual Color GetColor(const HitRecord& hit_rec) const override;

private:
  Color color_;
  Float min_value_, max_value_;
  LatticeNoisePtr noise_generator_;
};

using FractalBrownianMotionTexturePtr = FractalBrownianMotionTexture::FractalBrownianMotionTexturePtr;

} // namespace leptus

#endif // LEPTUS_TEXTURES_FBM_TEXTUE_H