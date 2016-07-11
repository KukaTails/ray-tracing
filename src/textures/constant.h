#ifndef LEPTUS_CONSTANT_H
#define LEPTUS_CONSTANT_H

#include "core/texture.h"
#include "core/hitrecord.h"

namespace leptus {

class ConstantColor : public Texture {
private:
  Color color_;
public:
  ConstantColor(Float r, Float g, Float b);
  explicit ConstantColor(const Color& color);
  void SetColor(const Color& color);
  virtual Color GetColor(const HitRecord& hit_rec) const override;
};


} // namespace leptus

#endif // LEPTUS_CONSTANT_H