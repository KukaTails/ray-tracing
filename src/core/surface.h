#ifndef LEPTUS_CORE_SURFACE_H
#define LEPTUS_CORE_SURFACE_H
#include <memory>

#include "accelerate/bounding_box.h"
#include "core/color.h"
#include "core/hitrecord.h"
#include "core/leptus.h"
#include "core/material.h"
#include "core/ray.h"
#include "core/sampler.h"

namespace leptus {

class Surface {
public:
  typedef std::shared_ptr<Surface> SurPtr;
  static const Float EPSILON;

protected:
  mutable MaterialPtr material_;
  SamplerPtr sampler_;
  mutable BoundingBoxPtr bounding_box_;

protected:
  bool BoundingBoxHit(const Ray& ray) const;
  virtual BoundingBoxPtr GetBoundingBox( ) const;
  virtual Point3f GetLocalHitPoint(const Point3f& p_hit) const = 0;

public:
  Surface(const Color& color = Color(0.5, 0.5, 0.5));
  Surface(const MaterialPtr& material);
  virtual ~Surface() = default;

  MaterialPtr material( ) const;
  void SetSampler(const SamplerPtr& sampler);
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const = 0;
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const = 0;
  
  virtual Point3f Sample( ) const;
  virtual Normal3f GetNormal(const Point3f& point) const;
  virtual Float ProbabilityDensityFunc(const HitRecord& hit_rec) const;
};

typedef Surface::SurPtr SurPtr;

} // namespace leptus

#endif // LEPTUS_CORE_SURFACE_H