#ifndef LEPTUS_CORE_VIEW_PLANE_H
#define LEPTUS_CORE_VIEW_PLANE_H
#include "core/leptus.h"

namespace leptus {

class ViewPlane {
public:
  unsigned h_res_, v_res_;
  Float pix_x_size_, pix_y_size_;

public:
  ViewPlane();
  ViewPlane(unsigned h_res, unsigned v_res);
  ViewPlane(unsigned h_res, unsigned v_res, Float pix_x_size, Float pix_y_size);
};

}  // namespace leptus

#endif // LEPTUS_CORE_VIEW_PLANE_H
