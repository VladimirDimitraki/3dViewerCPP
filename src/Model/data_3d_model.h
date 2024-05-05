#ifndef CPP4_3DVIEWER_V2_MODEL_DATA3DMODEL_H
#define CPP4_3DVIEWER_V2_MODEL_DATA3DMODEL_H

#include <iostream>
#include <vector>

namespace s21 {
///@brief Класс для хранения данных 3д модели
class Data3DModel {
 public:
  struct Coordinate {
    Coordinate() : x(0), y(0), z(0) {}
    double x, y, z;
  };
  Data3DModel() = default;
  ~Data3DModel() = default;

  std::vector<Coordinate> &GetCoordinateVertex();
  std::vector<int> &GetStringPolygon();
  void ClearData();

 private:
  std::vector<Coordinate> coordinates_vertex_;
  std::vector<int> string_polygon_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_DATA3DMODEL_H
