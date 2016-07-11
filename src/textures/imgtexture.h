#ifndef LEPTUS_IMGTEXTURE_H
#define LEPTUS_IMGTEXTURE_H
#include <iostream>

#include "core/color.h"
#include "core/image.h"
#include "core/texture.h"
#include "textures/mapping.h"

namespace leptus {

class ImageTexture : public Texture {
private:
  ImagePtr image_;
  MappingPtr mapper_;

public:
  ImageTexture(const std::string& image_path, const MappingPtr& mapper);
  ImageTexture(const ImagePtr& image, const MappingPtr& mapper);
  virtual Color GetColor(const HitRecord& hit_rec) const override;
};

} // namespace leptus

#endif // LEPTUS_IMGTEXTURE_H