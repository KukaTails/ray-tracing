#ifndef LEPTUS_VIEW_PLANE_H
#define LEPTUS_VIEW_PLANE_H

#include <memory>
#include <vector>

#include "core/leptus.h"
#include "geometry/geometry.h"

namespace leptus {

class ViewPlane {
public:
  unsigned h_res_, v_res_;
  Float pix_x_size_, pix_y_size_;
  std::shared_ptr<std::vector<Vector3f>> image_;

public:
  ViewPlane();
  ViewPlane(unsigned h_res, unsigned v_res);
  ViewPlane(unsigned h_res, unsigned v_res, Float pix_x_size, Float pix_y_size);
  void Save(std::string file_path) const;
};

}  // namespace leptus

#endif // LEPTUS_VIEW_PLANE_H
