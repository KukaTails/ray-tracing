#include "accelerate//bounding_box.h"

namespace leptus {

BoundingBox::BoundingBox(const Point3f& min, const Point3f& max)
  : min_(min), max_(max)
{}

Point3f BoundingBox::min( ) const
{
  return min_;
}

Point3f BoundingBox::max( ) const
{
  return max_;
}

bool BoundingBox::Hit(const Ray& ray) const
{
  Float ray_orig_x = ray.orig_.x_, ray_orig_y = ray.orig_.y_, ray_orig_z = ray.orig_.z_;
  Float ray_dir_x = ray.dir_.x_, ray_dir_y = ray.dir_.y_, ray_dir_z = ray.dir_.z_;

  Float tx_min = 0.0, ty_min = 0.0, tz_min = 0.0;
  Float tx_max = 0.0, ty_max = 0.0, tz_max = 0.0;

  Float a = 1.0 / ray_dir_x;
  if (a >= 0) {
    tx_min = (min_.x_ - ray_orig_x) * a;
    tx_max = (max_.x_ - ray_orig_x) * a;
  } else {
    tx_min = (max_.x_ - ray_orig_x) * a;
    tx_max = (min_.x_ - ray_orig_x) * a;
  }

  Float b = 1.0 / ray_dir_y;
  if (b >= 0) {
    ty_min = (min_.y_ - ray_orig_y) * b;
    ty_max = (max_.y_ - ray_orig_y) * b;
  } else {
    ty_min = (max_.y_ - ray_orig_y) * b;
    ty_max = (min_.y_ - ray_orig_y) * b;
  }

  Float c = 1.0 / ray_dir_z;
  if (c >= 0) {
    tz_min = (min_.z_ - ray_orig_z) * c;
    tz_max = (max_.z_ - ray_orig_z) * c;
  } else {
    tz_min = (max_.z_ - ray_orig_z) * c;
    tz_max = (min_.z_ - ray_orig_z) * c;
  }

  // find largest entering t value
  Float t0 = 0.0, t1 = 0.0;
  if (tx_min > ty_min)
    t0 = tx_min;
  else
    t0 = ty_min;
  if (tz_min > t0)
    t0 = tz_min;

  // find smallest exiting t value
  if (tx_max < ty_max)
    t1 = tx_max;
  else
    t1 = ty_max;
  if (tz_max < t1)
    t1 = tz_max;
  
  return t0 < t1 && t1 > BIAS;
}


} // namespace leptus