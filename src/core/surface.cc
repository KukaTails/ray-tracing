#include "core/surface.h"

#include "core/color.h"
#include "materials/matte.h"

namespace leptus {

Surface::Surface(const Color& color)
  :material_(std::make_shared<Matte>(color)), sampler_(), bounding_box_()
{}

Surface::Surface(const MaterialPtr& material)
  : material_(material), sampler_(), bounding_box_()
{}

BoundingBoxPtr Surface::GetBoundingBox( ) const
{
  return std::make_shared<BoundingBox>(Point3f( ), Point3f( ));
}

bool Surface::BoundingBoxHit(const Ray& ray) const
{
  if (!bounding_box_)
    bounding_box_ = GetBoundingBox( );

  if (!bounding_box_)
    return true;
  else
    return bounding_box_->Hit(ray);
}

MaterialPtr Surface::material( ) const
{
  return material_;
}

void Surface::SetSampler(const SamplerPtr& sampler)
{
  sampler_ = sampler;
}

Point3f Surface::Sample( ) const
{
  return Point3f( );
}

Float Surface::ProbabilityDensityFunc(const HitRecord& hit_rec) const
{
  return 0.0;
}

Normal3f Surface::GetNormal(const Point3f& point) const
{
  return Normal3f( );
}

} // namespace leptus