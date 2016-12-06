#ifndef LEPTUS_CORE_FRAME_H
#define LEPTUS_CORE_FRAME_H

#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <vector>

#include "geometry\geometry.h"

namespace leptus {

class Frame {
public:
  using Pointer = std::shared_ptr<Frame>;
  using PointProcessor = std::function<void(Vector3f&)>;

public:
  Frame(uint32_t size_x, uint32_t size_y);
  
  uint32_t GetXSize() const;
  uint32_t GetYSize() const;
  void Scale(float x);
  void PointProcessing(const PointProcessor& processor);
  void SetValue(uint32_t x, uint32_t y, const Vector3f& value);
  void AddValue(uint32_t x, uint32_t y, const Vector3f& value);
  const Vector3f& GetValue(uint32_t x, uint32_t y) const;
  void Save(const std::string& file_path) const;

private:
  uint32_t size_x_;
  uint32_t size_y_;
  std::shared_ptr<std::vector<Vector3f>> content_;
};

} // namespace leptus

#endif // LEPTUS_CORE_FRAME_H