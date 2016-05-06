#ifndef LEPTUS_SAMPLER_H
#define LEPTUS_SAMPLER_H
#include <vector>

#include "geometry/point.h"

namespace leptus {

class Sampler {
protected:
  unsigned num_samples_;
  unsigned num_set_;
  std::vector<Point2f> samples_;

public:
  static Float RandFloat( );

public:
  Sampler(unsigned num_samples, unsigned num_set);
  virtual ~Sampler( ) = default;
  virtual void GenerateSamples( ) = 0;
  Point2f SampleUnitSquare( ) const;
};

} // namespace leptus

#endif // LEPTUS_SAMPLER_H