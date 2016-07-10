#ifndef LEPTUS_TEXTURES_TURBULENCE_H
#define LEPTUS_TEXTURES_TURBULENCE_H
#include <memory>
#include "core/texture.h"
#include "core/lattice_noise.h"
#include "noise/cubic_noise.h"

namespace leptus {

class TurbulenceTexture : public Texture {
public:
  using TurbulenceTexturePtr = std::shared_ptr<TurbulenceTexture>;

public:
  TurbulenceTexture(const Color& color,
                    const LatticeNoisePtr& noise_generator = std::make_shared<CubicNoise>( ));
  TurbulenceTexture(const Color& color, Float min_value, Float max_value);
  TurbulenceTexture(const Color& color, unsigned int octave_num);
  TurbulenceTexture(const Color& color, Float min_value, Float max_value, unsigned int octave_num);

  Float min_value( ) const;
  Float max_value( ) const;
  void SetMinValue(Float min_value);
  void SetMaxValue(Float max_value);
  void SetOctaveNum(unsigned int value);
  virtual Color GetColor(const HitRecord& hit_rec) const override;

private:
  Color color_;
  Float min_value_, max_value_;
  LatticeNoisePtr noise_generator_;
};

using TurbulenceTexturePtr = TurbulenceTexture::TurbulenceTexturePtr;

} // namespace leptus

#endif // LEPTUS_TEXTURE_TURBULENCE_H