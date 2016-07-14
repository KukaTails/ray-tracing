#include "surfaces/triangle.h"
#include <algorithm>

namespace leptus {

Triangle::Triangle(const Point3f& p0, const Point3f& p1, const Point3f& p2, const Color& color)
  : Surface(color), p0_(p0), p1_(p1), p2_(p2), n_(Normalize(Cross(p2 - p0, p1 - p0)))
{}

Triangle::Triangle(const Point3f& p0, const Point3f& p1, const Point3f& p2, const MaterialPtr& material)
  : Surface(material), p0_(p0), p1_(p1), p2_(p2), n_(Normalize(Cross(p2 - p0, p1 - p0)))
{ }

Point3f Triangle::GetLocalHitPoint(const Point3f& p_hit) const
{
  return Point3f( );
}

BoundingBoxPtr Triangle::GetBoundingBox( ) const
{
  Float x_min = std::min({p0_.x_, p1_.x_, p2_.x_});
  Float y_min = std::min({p0_.y_, p1_.y_, p2_.y_});
  Float z_min = std::min({p0_.z_, p1_.z_, p2_.z_});

  Float x_max = std::max({p0_.x_, p1_.x_, p2_.x_});
  Float y_max = std::max({p0_.y_, p1_.y_, p2_.y_});
  Float z_max = std::max({p0_.z_, p1_.z_, p2_.z_});
  return std::make_shared<BoundingBox>(Point3f(x_min, y_min, z_min), Point3f(x_max, y_max, z_max));
}

bool Triangle::ShadowHit(const Ray& ray, Float& t_hit) const
{
  if (!BoundingBoxHit(ray))
    return false;

  Float a = p0_.x_ - p1_.x_, b = p0_.x_ - p2_.x_, c = ray.dir_.x_, d = p0_.x_ - ray.orig_.x_;
  Float e = p0_.y_ - p1_.y_, f = p0_.y_ - p2_.y_, g = ray.dir_.y_, h = p0_.y_ - ray.orig_.y_;
  Float i = p0_.z_ - p1_.z_, j = p0_.z_ - p2_.z_, k = ray.dir_.z_, l = p0_.z_ - ray.orig_.z_;
  Float m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
  Float q = g * i - e * k, s = e * j - f * i;

  Float inv_denom = 1.0 / (a * m + b * q + c * s);
  Float e1 = d * m - b * n - c * p;
  Float beta = e1 * inv_denom;

  if (beta < 0.0)
    return false;

  Float r = e * l - h * i;
  Float e2 = a * n + d * q + c * r;
  Float gamma = e2 * inv_denom;

  if (gamma < 0.0)
    return false;

  if (beta + gamma > 1.0)
    return false;

  Float e3 = a * p - b * r + d * s;
  Float t = e3 * inv_denom;

  if (t < EPSILON)
    return false;
  t_hit = t;
  return true;
}

bool Triangle::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{
  if (ShadowHit(ray, t_hit)) {
    hit_rec.n_hit_ = n_;
    hit_rec.p_hit_ = ray.orig_ + t_hit * ray.dir_;
    return true;
  }
  return false;
}

} // namespace leptus