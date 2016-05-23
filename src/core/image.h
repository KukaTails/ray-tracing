#ifndef LEPTUS_IMAGE_H
#define LEPTUS_IMAGE_H
#include <memory>
#include "core/color.h"

namespace leptus {

class Image {
public:
  typedef std::shared_ptr<Image> ImagePtr;
public:
  Color GetColor(unsigned row, unsigned column) const
  { 
    return Color(0.0, 0.0, 0.0);
  }
};

typedef Image::ImagePtr ImagePtr;

} // namespace leptus

#endif // LEPTUS_IMAGE_H