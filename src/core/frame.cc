#include "core/frame.h"

#include <fstream>
#include <algorithm>

namespace leptus {

Frame::Frame(uint32_t size_x, uint32_t size_y)
  : size_x_(size_x),
  size_y_(size_y),
  content_(std::make_shared<std::vector<Vector3f>>(size_x * size_y))
{ }


uint32_t Frame::GetXSize() const
{
  return size_x_;
}


uint32_t Frame::GetYSize() const
{
  return size_y_;
}


void Frame::SetValue(uint32_t x, uint32_t y, const Vector3f& value)
{
  assert(x * y + y <= size_x_ * size_y_);
  (*content_)[y * size_x_ + x] = value;
}

void Frame::AddValue(uint32_t x, uint32_t y, const Vector3f& value)
{
  assert(x * y + y <= size_x_ * size_y_);
  (*content_)[y * size_x_ + x] += value;
}

const Vector3f& Frame::GetValue(uint32_t x, uint32_t y) const
{
  assert(x * y + y <= size_x_ * size_y_);
  return (*content_)[y * size_x_ + x];
}


void Frame::PointProcessing(const PointProcessor& processor)
{
  std::for_each(content_->begin(), content_->end(), processor);
}


void Frame::Scale(float x)
{
  std::for_each(content_->begin(), content_->end(), [x](Vector3f& color) {
    color.x_ *= x;
    color.y_ *= x;
    color.z_ *= x;
  });
}


void Frame::Save(const std::string& file_path) const
{
  std::ofstream ofs(file_path + ".ppm", std::ios::out | std::ios::binary);
  int h_res = size_x_, v_res = size_y_;

  ofs << "P6\n" << h_res << " " << v_res << "\n255\n";
  for (unsigned i = 0; i < h_res * v_res; ++i) {
    ofs << (unsigned char)(std::min(float(1.0), (*content_)[i].x_) * 255)
      << (unsigned char)(std::min(float(1.0), (*content_)[i].y_) * 255)
      << (unsigned char)(std::min(float(1.0), (*content_)[i].z_) * 255);
  }
}

} // namespace leptus