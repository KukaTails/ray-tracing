#include "core/sampler.h"

namespace leptus {

Sampler::Sampler(unsigned num_samples, unsigned num_sets)
  : num_samples_(num_samples), num_sets_(num_sets), cnt_(0)
{ }

Float Sampler::RandFloat( )
{
  const int range = 1000;
  return static_cast<Float>(rand( ) % 1000) / 1000.0;
}

Point2f Sampler::SampleUnitSquare( )
{
  return samples_[(cnt_++) % (num_samples_ * num_sets_)];
}

unsigned Sampler::num_samples( ) const
{
  return num_samples_;
}

} // namespace leptus