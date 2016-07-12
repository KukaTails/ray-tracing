#include "samplers/random.h"

namespace leptus {

RandomSampler::RandomSampler(unsigned num_samples, unsigned num_sets)
  : Sampler(num_samples, num_sets)
{ }

void RandomSampler::GenerateSamples( )
{
  for (int k = 0; k < num_sets_; ++k) {
    for (int i = 0; i < num_samples_; ++i) {
      Point2f sample_point(RandFloat( ), RandFloat( ));
      square_samples_.push_back(sample_point);
    }
  }
}

} // namespace leptus