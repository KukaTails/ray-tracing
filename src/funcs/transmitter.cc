#include "funcs/transmitter.h"

namespace leptus {

PerfectTransmitter::PerfectTransmitter(Float refractive_index, Float k_transmit)
  : refractive_index_(refractive_index), k_transmit_(k_transmit)
{ }

bool PerfectTransmitter::TotalInternalReflection(const Ray& ray, const HitRecord& hit_rec) const
{
  Vector3f out_dir = -ray.dir_;
  Float cos_theta = Dot(hit_rec.n_hit_, out_dir);
  Float eta = refractive_index_;

  if (cos_theta < 0.0)
    eta = 1.0 / eta;
  return (1.0 - (1.0 - cos_theta * cos_theta) / (eta * eta)) < 0.0;
}

Color PerfectTransmitter::SampleF(const HitRecord& hit_rec,
                                  const Vector3f& out_dir,
                                  Vector3f& refractive_dir) const
{
  Normal3f normal = hit_rec.n_hit_;
  //if (Dot(normal, out_dir) < 0.0)
  //  normal = -normal;
  Float cos_theta_i = Dot(normal, out_dir);
  Float eta = refractive_index_;

  if (cos_theta_i < 0.0) {
    cos_theta_i = -cos_theta_i;
    normal = -normal;
    eta = 1.0 / eta;
  }

  Float cos_theta_2 = sqrt(1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
  refractive_dir = -out_dir / eta - (cos_theta_2 - cos_theta_i / eta) * Vector3f(normal);
  return (k_transmit_ / (eta * eta) / fabs(Dot(hit_rec.n_hit_, out_dir))) * WHITE;
}

} // namespace leptus