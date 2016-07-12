#ifndef LEPTUS_RANDOM_H
#define LEPTUS_RANDOM_H

#include "core/sampler.h"

namespace leptus {

class RandomSampler : public Sampler {
public:
  RandomSampler(unsigned num_samples, unsigned num_sets);
  virtual void GenerateSamples( ) override;
};

} // namespace leptus

#endif // LEPTUS_RANDOM_H