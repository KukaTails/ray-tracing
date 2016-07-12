#ifndef LEPTUS_JITTER_H
#define LEPTUS_JITTER_H

#include "core/sampler.h"

namespace leptus {

class JitterSampler : public Sampler {
public:
  JitterSampler(unsigned num_samples, unsigned num_sets);
  virtual void GenerateSamples( ) override;
};

} // namespace leptus

#endif // LEPTUS_JITTER_H