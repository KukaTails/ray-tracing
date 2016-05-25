#ifndef LEPTUS_CORE_TEXTURE_H
#define LEPTUS_CORE_TEXTURE_H

#include <memory>

#include "core/color.h"
#include "core/hitrecord.h"

namespace leptus {

class Texture {
public:
  typedef std::shared_ptr<Texture> TexturePtr;
public:
  virtual ~Texture( ) = default;
  virtual Color GetColor(const HitRecord& hit_rec) const = 0;
};

typedef Texture::TexturePtr TexturePtr;

} // namespace leptus

#endif // LEPTUS_CORE_TEXTURE_H