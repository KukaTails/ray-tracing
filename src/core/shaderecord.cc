#include "core/shaderecord.h"

#include "tracers/whitted.h"

namespace leptus {

ShadeRecord::ShadeRecord(const World& world)
  : world_(world), is_hit_(false), color_(BLACK), tracer_(WhittedTracer())
{ }

ShadeRecord::ShadeRecord(const ShadeRecord& shade_rec, const Tracer& tracer)
  : tracer_(tracer), world_(shade_rec.world_)
{
  this->color_ = shade_rec.color_;
  this->dir_ = shade_rec.dir_;
  this->hit_rec_ = shade_rec.hit_rec_;
  this->is_hit_ = shade_rec.is_hit_;
  this->material_ = shade_rec.material_;
  this->p_texture_ = shade_rec.p_texture_;
  this->ray_ = shade_rec.ray_;
}

} // namespace leptus