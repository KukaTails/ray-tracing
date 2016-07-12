#include "surfaces/rectangle.h"
#include <algorithm>

namespace leptus {

Rectangle::Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const Color& color)
  : Surface(color), p_(p), a_(a), b_(b), n_(Normalize(Cross(a, b))), pdf_(1 / (Cross(a, b).Length()))
{
  Assert(Dot(a, b) == 0.0);
}

Rectangle::Rectangle(const Point3f& p, const Vector3f& a, const Vector3f& b, const MaterialPtr& material)
  : Surface(material), p_(p), a_(a), b_(b), n_(Normalize(Cross(a, b)))
{
  Assert(Dot(a, b) == 0.0);
}

Rectangle::Rectangle(const Point3f& p, const Vector3f& a,
                     const Vector3f& b, const Normal3f& n, const MaterialPtr& material)
  : Surface(material), p_(p), a_(a), b_(b), n_(Normalize(n))
{
  Assert(Dot(a, b) == 0.0);
}

Point3f Rectangle::GetLocalHitPoint(const Point3f& p_hit) const
{
  const Vector3f segment = p_hit - p_;
  const Float rect_x_unit_len = b_.Length( ) / 2;
  const Float rect_z_unit_len = a_.Length( ) / 2;
  Float x_coord = (Dot(Vector3f(segment), Normalize(b_)) - b_.Length() / 2) / rect_x_unit_len;
  Float z_coord = (Dot(Vector3f(segment), Normalize(a_)) - a_.Length() / 2) / rect_z_unit_len;
  return Point3f(x_coord, 0.0f, z_coord);
}

BoundingBoxPtr Rectangle::GetBoundingBox( ) const
{
  Point3f p0 = p_;
  Point3f p1 = p_ + a_;
  Point3f p2 = p_ + b_;

  Float x_min = std::min({p0.x_, p1.x_, p2.x_});
  Float y_min = std::min({p0.y_, p1.y_, p2.y_});
  Float z_min = std::min({p0.z_, p1.z_, p2.z_});

  Float x_max = std::max({p0.x_, p1.x_, p2.x_});
  Float y_max = std::max({p0.y_, p1.y_, p2.y_});
  Float z_max = std::max({p0.z_, p1.z_, p2.z_});
  return std::make_shared<BoundingBox>(Point3f(x_min, y_min, z_min), Point3f(x_max, y_max, z_max));
}

bool Rectangle::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  Float t = Dot(p_ - ray.orig_, n_) / Dot(ray.dir_, n_);
  if (abs(t) <= EPSILON)
    return false;

  Point3f p_hit = ray.orig_ + t * ray.dir_;
  Vector3f d = p_hit - p_;
  Float d_dot_a = Dot(d, a_), d_dot_b = Dot(d, b_);

  if (d_dot_a < 0.0 || d_dot_a > Dot(a_, a_))
    return false;
  if (d_dot_b < 0.0 || d_dot_b > Dot(b_, b_))
    return false;
  t_hit = t;
  hit_rec.p_hit_ = p_hit;
  hit_rec.n_hit_ = n_;
  hit_rec.local_p_hit_ = GetLocalHitPoint(p_hit);
  return true;
}

bool Rectangle::ShadowHit(const Ray& ray, Float& t_hit) const
{
  if (!BoundingBoxHit(ray))
    return false;

  return Hit(ray, t_hit, HitRecord( ));
}

Point3f Rectangle::Sample( ) const
{
  Point2f sampler_point = sampler_->SampleUnitSquare( );
  return p_ + sampler_point.x_ * a_ + sampler_point.y_ * b_;
}

Float Rectangle::ProbabilityDensityFunc(const HitRecord& hit_rec) const
{
  return pdf_;
}

} // namespace leptus