#include "surfaces/disk.h"

#include "geometry/geometry.h"

namespace leptus {

Disk::Disk(const Point3f& center, Float radius, const Normal3f& n, const MaterialPtr& material)
  : Surface(material), center_(center), radius_(radius), n_(Normalize(n)), pdf_(1.0 / (2 * M_PI * radius * radius))
{}

Point3f Disk::GetLocalHitPoint(const Point3f& p_hit) const
{
  Point3f tmp = Point3f(p_hit.x_ - center_.x_, p_hit.y_ - center_.y_, p_hit.z_ - center_.z_);
  return tmp * (1 / radius_);
}

Point3f Disk::Sample( ) const
{
  Point2f sample_point = sampler_->SampleUnitDisk( );
  Float a = n_.x_, b = n_.y_, c = n_.z_;
  Vector3f u = Normalize(Vector3f(0, -c, b));
  Vector3f v = Normalize(Vector3f(b * b + c * c, -a * b, -a * c));
  return center_ + sample_point.x_ * u * radius_ + sample_point.y_ * v * radius_;
}

Normal3f Disk::GetNormal(const Point3f& point) const
{
  return n_;
}

Float Disk::ProbabilityDensityFunc(const HitRecord& hit_rec) const
{
  return pdf_;
}

bool Disk::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  Float t = Dot((center_ - ray.orig_), n_) / Dot(ray.dir_, n_);
  if (abs(t) <= EPSILON)
    return false;

  Point3f p_hit = ray.orig_ + t * ray.dir_;
  Float distance = Distance(p_hit, center_);
  if (distance < radius_) {
    t_hit = t;
    hit_rec.n_hit_ = n_;
    hit_rec.p_hit_ = p_hit;
    return true;
  }
  return false;
}

bool Disk::ShadowHit(const Ray& ray, Float& t_hit) const
{
  return Hit(ray, t_hit, HitRecord( ));
}

} // namespace leptus