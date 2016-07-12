#ifndef LEPTUS_REGULAR_H
#define LEPTUS_REGULAR_H

#include "core/sampler.h"

namespace leptus {

class RegularSampler : public Sampler {
public:
  RegularSampler(unsigned num_samples, unsigned num_sets);
  virtual void GenerateSamples( ) override;
};

} // namespace leptus

#endif // LEPTUS_REGULAR_H