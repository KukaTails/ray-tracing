#include "surfaces/grid.h"
#include <limits>
#include <algorithm>

namespace leptus {

const Float Grid::MULTOPLIER = 2.0;

Point3f Grid::GetMinCoordinate( ) const
{
  Point3f min_coordinate(std::numeric_limits<Float>::infinity());

  for (auto& surface : surfaces_) {
    Point3f min = surface->GetBoundingBox( )->min( );
    min_coordinate.x_ = std::min(min_coordinate.x_, min.x_);
    min_coordinate.y_ = std::min(min_coordinate.y_, min.y_);
    min_coordinate.z_ = std::min(min_coordinate.z_, min.z_);
  }
  return Point3f(min_coordinate - Point3f(EPSILON));
}

Point3f Grid::GetMaxCoordinate( ) const
{
  Point3f max_coordinate(std::numeric_limits<Float>::lowest());

  for (auto& surface : surfaces_) {
    Point3f max = surface->GetBoundingBox( )->max( );
    max_coordinate.x_ = std::max(max_coordinate.x_, max.x_);
    max_coordinate.y_ = std::max(max_coordinate.y_, max.y_);
    max_coordinate.z_ = std::max(max_coordinate.z_, max.z_);
  }
  return Point3f(max_coordinate + Point3f(EPSILON));
}

void Grid::SetupCells( )
{
  Point3f min_point = GetMinCoordinate( );
  Point3f max_point = GetMaxCoordinate( );
  bounding_box_ = std::make_shared<BoundingBox>(min_point, max_point);

  int surfaces_num = surfaces_.size( );
  Float x_len = max_point.x_ - min_point.x_;
  Float y_len = max_point.y_ - min_point.y_;
  Float z_len = max_point.z_ - min_point.z_;

  Float s = std::pow(x_len * y_len * z_len / surfaces_num, 0.3333333);
  num_x_ = MULTOPLIER * x_len / s + 1.0;
  num_y_ = MULTOPLIER * y_len / s + 1.0;
  num_z_ = MULTOPLIER * z_len / s + 1.0;

  int cells_num = num_x_ * num_y_ * num_z_;
  cells_.reserve(cells_num);
  for (int i = 0; i < cells_.size( ); ++i)
    cells_.push_back(nullptr);

  std::vector<int> counts(cells_num);
  Point3f grid_min = bounding_box_->min( );
  Point3f grid_max = bounding_box_->max( );
  for (auto& surface : surfaces_) {
    BoundingBoxPtr bounding_box = surface->GetBoundingBox( );
    Point3f surface_min = bounding_box->min( );
    Point3f surface_max = bounding_box->max( );

    int ix_min = Clamp((surface_min.x_ - grid_min.x_) * num_x_ / x_len, 0.0f, num_x_ - 1);
    int iy_min = Clamp((surface_min.y_ - grid_min.y_) * num_y_ / y_len, 0.0f, num_x_ - 1);
    int iz_min = Clamp((surface_min.z_ - grid_min.z_) * num_z_ / z_len, 0.0f, num_x_ - 1);
    int ix_max = Clamp((surface_max.x_ - grid_min.x_) * num_x_ / x_len, 0.0f, num_x_ - 1);
    int iy_max = Clamp((surface_max.y_ - grid_min.y_) * num_y_ / y_len, 0.0f, num_x_ - 1);
    int iz_max = Clamp((surface_max.z_ - grid_min.z_) * num_z_ / z_len, 0.0f, num_x_ - 1);

    for (int iz = iz_min; iz <= iz_max; ++iz) {
      for (int iy = iy_min; iy <= iy_max; ++iy) {
        for (int ix = ix_min; ix <= ix_max; ++ix) {
          int index = ix + num_x_ * iy + num_x_ * num_y_ * iz;
          if (!cells_[index]) {
            cells_[index] = surface;
            counts[index] += 1;
            index = 1;
          } else {
            if (counts[index] == 1) {
              CompoundSurfacePtr compound_surface = std::make_shared<CompoundSurface>( );
              compound_surface->AddSurface(cells_[index]);
              compound_surface->AddSurface(surface);
              cells_[index] = compound_surface;
              counts[index] += 1;
            } else {
              dynamic_cast<CompoundSurface*>(&*cells_[index])->AddSurface(surface);
              counts[index] += 1;
            }
          }
        }
      }
    }
  }
  surfaces_.erase(std::begin(surfaces_), std::end(surfaces_));
}


bool Grid::ShadowHit(const Ray& ray, Float& t_hit) const
{
  return true;
}

bool Grid::Hit(const Ray& ray, Float& t_hit, HitRecord& hit_rec) const
{

}

} // namespace leptus