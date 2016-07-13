#ifndef LEPTUS_SURFACES_GRID_H
#define LEPTUS_SURFACES_GRID_H
#include "surfaces/compound.h"

namespace leptus {

class Grid : public CompoundSurface {
public:
  void SetupCells( );
  virtual bool Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const override;
  virtual bool ShadowHit(const Ray& ray, Float& t_hit) const override;

private:
  Point3f GetMinCoordinate( ) const;
  Point3f GetMaxCoordinate( ) const;

private:
  Float num_x_, num_y_, num_z_; // cells on x, y, z direction
  std::vector<SurPtr> cells_;

private:
  static const Float MULTOPLIER;
};

} // namespace leptus

#endif // LEPTUS_SURFACES_GRID_H