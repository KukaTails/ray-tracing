#ifndef LEPTUS_MAPPING_H
#define LEPTUS_MAPPING_H
#include <memory>
#include "geometry/geometry.h"

namespace leptus {

class Mapping {
public:
  typedef std::shared_ptr<Mapping> MappingPtr;
public:
  virtual ~Mapping( ) = default;
  virtual Point2f GetTextureCoordinates(const Point3f& local_hit_point) const = 0;
};

typedef Mapping::MappingPtr MappingPtr;


class SphericalMapping : public Mapping {
public:
  virtual Point2f GetTextureCoordinates(const Point3f& local_hit_point) const override;
};

class RectanglelMapping : public Mapping {
public:
  virtual Point2f GetTextureCoordinates(const Point3f& local_hit_point) const override;
};

} // namespace leptus

#endif // LEPTUS_MAPPING_H