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
  if (square_samples_.size( ) == 0) {
    GenerateSamples( );
  }
  return square_samples_[(cnt_++) % (num_samples_ * num_sets_)];
}

Point2f Sampler::SampleUnitDisk( )
{
  if (disk_samples_.size( ) == 0) {
    if (square_samples_.size( ) == 0)
      GenerateSamples( );
    MapSamplesToUnitDisk( );
  }
  return disk_samples_[(cnt_++) % (num_samples_ * num_sets_)];
}

unsigned Sampler::num_samples( ) const
{
  return num_samples_;
}

void Sampler::MapSamplesToUnitDisk( )
{
  int size = square_samples_.size( );
  disk_samples_.reserve(size);
  for (int i = 0; i < size; ++i) {
    Point2f p;
    Float r, phi;

    p.x_ = 2.0 * square_samples_[i].x_ - 1.0;
    p.y_ = 2.0 * square_samples_[i].y_ - 1.0;
    if (p.x_ > -p.y_) {
      if (p.x_ > p.y_) {
        r = p.x_;
        phi = p.y_ / p.x_;
      } else {
        r = p.y_;
        phi = 2 - p.x_ / p.y_;
      }
    } else {
      if (p.x_ < p.y_) {
        r = -p.x_;
        phi = 4 + p.y_ / p.x_;
      } else {
        r = -p.y_;
        if (p.y_ != 0.0)
          phi = 6 - p.x_ / p.y_;
        else
          phi = 0.0;
      }
    }
    phi *= M_PI / 4.0;
    disk_samples_.push_back(Point2f(r * std::cos(phi), r * std::sin(phi)));
  }
}

void Sampler::MapSamplesToHemisphere(Float e)
{
}

} // namespace leptus