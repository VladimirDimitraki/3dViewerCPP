#include "data_3d_model.h"

namespace s21 {
void Data3DModel::ClearData() {
  coordinates_vertex_.clear();
  string_polygon_.clear();
}

std::vector<Data3DModel::Coordinate> &Data3DModel::GetCoordinateVertex() {
  return coordinates_vertex_;
}

std::vector<int> &Data3DModel::GetStringPolygon() { return string_polygon_; }

}  // namespace s21