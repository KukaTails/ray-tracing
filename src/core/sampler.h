#ifndef LEPTUS_CORE_SAMPLER_H
#define LEPTUS_CORE_SAMPLER_H
#include <vector>
#include <memory>

#include "geometry/geometry.h"

namespace leptus {

class Sampler {
public:
  using SamplerPtr = std::shared_ptr<Sampler>;

public:
  static Float RandFloat( );

public:
  Sampler(unsigned num_samples, unsigned num_sets);
  virtual ~Sampler( ) = default;
  
  unsigned num_samples( ) const;
  Point2f SampleUnitSquare( );
  Point2f SampleUnitDisk( );
  Point3f SampleUnitHemiSphere( );
  void SetHemiSphereCosineExponent(Float cosine_exponent);
  virtual void GenerateSamples( ) = 0;

protected:
  void MapSamplesToUnitDisk( );
  void MapSamplesToHemisphere(Float cosine_exponent_);

private:
  void Init( );
  unsigned GetIndex();

protected:
  unsigned num_samples_;
  unsigned num_sets_;
  unsigned cnt_;
  Float cosine_exponent_;
  std::vector<Point3f> hemisphere_samples_;
  std::vector<Point2f> square_samples_;
  std::vector<Point2f> disk_samples_;
  std::vector<unsigned> shuffled_indices_;
  unsigned sample_point_jumped_ = 0;
};

using SamplerPtr = Sampler::SamplerPtr;

} // namespace leptus

#endif // LEPTUS_CORE_SAMPLER_H