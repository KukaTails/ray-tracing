#include "samplers/jitter.h"

namespace leptus {

JitterSampler::JitterSampler(unsigned num_samples, unsigned num_sets)
  : Sampler(pow(static_cast<int>(sqrt(num_samples)), 2), num_sets)
{ }

void JitterSampler::GenerateSamples( )
{
  int n = static_cast<unsigned>(sqrt(num_samples_));

  for (int k = 0; k < num_sets_; ++k) {
    for (int y = 0; y < n; ++y) {
      for (int x = 0; x < n; ++x) {
        Point2f sample_point((x + RandFloat( )) / n, (y + RandFloat( )) / n);
        square_samples_.push_back(sample_point);
      }
    }
  }
}

} // namespace leptus