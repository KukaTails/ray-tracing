#ifndef LEPTUS_IMAGE_H
#define LEPTUS_IMAGE_H
#include <string>
#include <memory>

#include "core/color.h"

namespace leptus {

class Image {
public:
  typedef std::shared_ptr<Image> ImagePtr;
public:
  explicit Image(const std::string& image_path);
  ~Image( );
  Image(const Image&) = delete;
  bool operator=(const Image&) = delete;
  Color GetColor(float u, float v) const;
  
private:
  void LoadImage( );
  void Free( );

private:
  std::string image_path_;
  unsigned char *data_;
  int width_, height_;
  bool success = false;
};

typedef Image::ImagePtr ImagePtr;

} // namespace leptus

#endif // LEPTUS_IMAGE_H