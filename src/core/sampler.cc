#include "core/sampler.h"

namespace leptus {

Sampler::Sampler(unsigned num_samples, unsigned num_sets)
  : num_samples_(num_samples), num_sets_(num_sets), cnt_(0), cosine_exponent_(0.5)
{ }

void Sampler::SetHemiSphereCosineExponent(Float cosine_exponent)
{
  Assert(cosine_exponent >= 0.0);
  cosine_exponent_ = cosine_exponent;
}

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

Point3f Sampler::SampleUnitHemiSphere( )
{
  if (hemisphere_samples_.size( ) == 0) {
    if (square_samples_.size( ) == 0)
      GenerateSamples( );
    MapSamplesToHemisphere(cosine_exponent_);
  }
  return hemisphere_samples_[(cnt_++) % (num_samples_ * num_sets_)];
}

unsigned Sampler::num_samples( ) const
{
  return num_samples_;
}

void Sampler::MapSamplesToUnitDisk( )
{
  const int size = square_samples_.size( );
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
  const int size = square_samples_.size( );
  hemisphere_samples_.reserve(num_samples_ * num_sets_);
  for (int i = 0; i < size; ++i) {
    Float cos_phi = std::cos(2.0 * M_PI * square_samples_[i].x_);
    Float sin_phi = std::sin(2.0 * M_PI * square_samples_[i].x_);
    Float cos_theta = std::pow(1.0 - square_samples_[i].y_, 1.0 / (1.0 + e));
    Float sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);
    Float point_u = sin_theta * cos_phi;
    Float point_v = sin_theta * sin_phi;
    Float point_w = cos_theta;
    hemisphere_samples_.push_back(Point3f(point_u, point_v, point_w));
  }
}

} // namespace leptus