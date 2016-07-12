#ifndef LEPTUS_CORE_SAMPLER_H
#define LEPTUS_CORE_SAMPLER_H
#include <vector>
#include <memory>

#include "geometry/geometry.h"

namespace leptus {

class Sampler {
public:
  using SamplerPtr = std::shared_ptr<Sampler>;

public:
  static Float RandFloat( );

public:
  Sampler(unsigned num_samples, unsigned num_sets);
  virtual ~Sampler( ) = default;
  
  unsigned num_samples( ) const;
  Point2f SampleUnitSquare( );
  Point2f SampleUnitDisk( );
  void MapSamplesToUnitDisk( );
  void MapSamplesToHemisphere(Float e);
  virtual void GenerateSamples( ) = 0;

protected:
  unsigned num_samples_;
  unsigned num_sets_;
  unsigned cnt_;
  std::vector<Point2f> square_samples_;
  std::vector<Point2f> disk_samples_;
};

using SamplerPtr = Sampler::SamplerPtr;

} // namespace leptus

#endif // LEPTUS_CORE_SAMPLER_H