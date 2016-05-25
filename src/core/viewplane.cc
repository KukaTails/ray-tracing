#include "core/viewplane.h"

namespace leptus {

ViewPlane::ViewPlane( )
  :h_res_(640), v_res_(480), pix_x_size_(1.0 / 640.0), pix_y_size_(1.0 / 480.0)
{ }

ViewPlane::ViewPlane(unsigned h_res, unsigned v_res)
  : h_res_(h_res), v_res_(v_res), pix_x_size_(1.0 / h_res), pix_y_size_(1.0 / v_res)
{ }

ViewPlane::ViewPlane(unsigned h_res, unsigned v_res, Float pix_x_size, Float pix_y_size)
  : h_res_(h_res), v_res_(v_res), pix_x_size_(pix_x_size), pix_y_size_( )
{ }

} // namespace leptus