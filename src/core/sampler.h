#ifndef LEPTUS_CORE_SAMPLER_H
#define LEPTUS_CORE_SAMPLER_H
#include <vector>
#include <memory>

#include "geometry/geometry.h"

namespace leptus {

class Sampler {
protected:
  unsigned num_samples_;
  unsigned num_sets_;
  unsigned cnt_;
  std::vector<Point2f> samples_;

public:
  typedef std::shared_ptr<Sampler> SamplerPtr;
  static Float RandFloat( );

public:
  Sampler(unsigned num_samples, unsigned num_sets);
  virtual ~Sampler( ) = default;
  virtual void GenerateSamples( ) = 0;
  Point2f SampleUnitSquare( );
  unsigned num_samples( ) const;
};

typedef Sampler::SamplerPtr SamplerPtr;

} // namespace leptus

#endif // LEPTUS_CORE_SAMPLER_H