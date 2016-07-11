#ifndef LEPTUS_PROCESS_H
#define LEPTUS_PROCESS_H

#include <functional>

#include "core/texture.h"

namespace leptus {

Color Checker3D(const Point3f& point);

class ProcessTexture : public Texture {
public:
  typedef std::function<Color(const Point3f&)> TextureFunc;
private:
  TextureFunc process_;
public:
  ProcessTexture(const TextureFunc& process);
  virtual Color GetColor(const HitRecord& hit_rec) const override;
};

} // namespace leptus

#endif // LEPTUS_PROCESS_H