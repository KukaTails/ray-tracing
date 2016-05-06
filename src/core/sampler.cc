#include "core/sampler.h"

namespace leptus {

Sampler::Sampler(unsigned num_samples, unsigned num_set)
  : num_samples_(num_samples), num_set_(num_set)
{ }

Float Sampler::RandFloat( )
{
  const int range = 1000;
  return static_cast<Float>(rand( ) % 1000) / 1000.0;
}

} // namespace leptus