#include "textures/imgtexture.h"

#include <fstream>

namespace leptus {

ImageTexture::ImageTexture(const std::string& image_path, const MappingPtr& mapper)
  : image_(std::make_shared<Image>(image_path)), mapper_(mapper)
{ }

ImageTexture::ImageTexture(const ImagePtr& image, const MappingPtr& mapper)
  : image_(image), mapper_(mapper)
{ }


Color ImageTexture::GetColor(const HitRecord& hit_rec) const
{
  if (!mapper_) {
    std::cout << "No mapper" << std::endl;
    return Color(1.0f, 0.0f, 0.0f);
  }
  const Point3f& local_p_hit = hit_rec.local_p_hit_;
  const Point2f& texture_coords = mapper_->GetTextureCoordinates(local_p_hit);
  return image_->GetColor(texture_coords.x_, texture_coords.y_);
}

} // namespace leptus