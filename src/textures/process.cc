#include "textures/process.h"

namespace leptus {

ProcessTexture::ProcessTexture(const TextureFunc& process)
  : process_(process)
{ }

Color ProcessTexture::GetColor(const HitRecord& hit_rec) const
{
  return process_(hit_rec.p_hit_);
}

Color Checker3D(const Point3f& point)
{
  const Float size = 100.0f;
  const Float BIAS = -0.000187453738;
  const Float x = point.x_ + BIAS, y = point.y_ + BIAS, z = point.z_ + BIAS;

  if ((static_cast<int>(floor(x / size)) +
       static_cast<int>(floor(y / size)) +
       static_cast<int>(floor(z / size))) % 2 == 0)
    return Color(0.0, 0.0, 0.0);
  else
    return Color(1.0, 1.0, 1.0);
}

Color CheckerForPlane(const Point3f& local_p)
{
  const Float size = 0.1;
  const Float out_line_width = 0.01;
  Float x = local_p.x_, y = local_p.y_, z = local_p.z_;
  int i_x = static_cast<int>(std::floor(x / size));
  int i_z = static_cast<int>(std::floor(z / size));
  Float f_x = x / size - i_x;
  Float f_z = z / size - i_z;
  Float width = 0.5 * out_line_width * size;
  if ((f_x < width || f_x > 1.0 - width) || (f_z < width || f_z > 1.0 - width)) {
    return Color(0.0, 0.0, 0.5);
  } else {
    if ((i_x + i_z) % 2 == 0)
      return Color(0, 0, 0);
    else
      return Color(1, 1, 1);
  }
}



} // namespace leptus