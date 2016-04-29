#include <algorithm>
#include <fstream>

#include "core/viewplane.h"

namespace leptus {

ViewPlane::ViewPlane()
  :h_res_(640), v_res_(480), pix_x_size_(1.0 / 640.0), pix_y_size_(1.0 / 480.0)
{
  image_ = std::make_shared<std::vector<Vector3f>>(v_res_ * h_res_);
}

ViewPlane::ViewPlane(unsigned h_res, unsigned v_res)
  : h_res_(h_res), v_res_(v_res), pix_x_size_(1.0 / h_res), pix_y_size_(1.0 / v_res)
{
  image_ = std::make_shared<std::vector<Vector3f>>(v_res * h_res);
}

ViewPlane::ViewPlane(unsigned h_res, unsigned v_res, Float pix_x_size, Float pix_y_size)
  :h_res_(h_res), v_res_(v_res), pix_x_size_(pix_x_size), pix_y_size_()
{
  image_ = std::make_shared<std::vector<Vector3f>>(v_res * h_res);
}

void ViewPlane::Save(std::string file_path) const
{
  std::ofstream ofs(file_path, std::ios::out | std::ios::binary);

  ofs << "P6\n" << h_res_ << " " << v_res_ << "\n255\n";
  for (unsigned i = 0; i < h_res_ * v_res_; ++i) {
    ofs << (unsigned char)(std::min(float(1), (*image_)[i].x_) * 255) <<
      (unsigned char)(std::min(float(1), (*image_)[i].y_) * 255) <<
      (unsigned char)(std::min(float(1), (*image_)[i].z_) * 255);
  }
  ofs.close();
}

} // namespace leptus