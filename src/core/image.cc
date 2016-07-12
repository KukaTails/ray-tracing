#include <cmath>
#include <algorithm>
#include "image.h"
#include "SOIL/SOIL.h"

namespace leptus {

Image::Image(const std::string& image_path)
  : image_path_(image_path)
{
  LoadImage( );
}

void Image::LoadImage( )
{
  data_ = SOIL_load_image(image_path_.c_str( ), &width_, &height_, 0, SOIL_LOAD_RGB);
  if (!data_) {
    std::cout << "LOAD IMAGE FAILURE: image name = " + image_path_;
    return;
  }
  success = true;
}

Color Image::GetColor(float u, float v) const
{
  assert(u >= 0 && v >= 0);
  int x = std::max(0, static_cast<int>(ceil(u * width_) - 1));
  int y = std::max(0, static_cast<int>(ceil(v * height_) - 1));
  int index = (y * width_ + x) * 3;
  return Color(static_cast<float>(data_[index]) / 256.0f,
               static_cast<float>(data_[index + 1]) / 256.0f,
               static_cast<float>(data_[index + 2])/ 256.0f);
}

void Image::Free( )
{
  if (data_)
    SOIL_free_image_data(data_);
}

Image::~Image( )
{
  Free( );
}

} // namespace leptus