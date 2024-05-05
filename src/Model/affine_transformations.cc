#include "affine_transformations.h"

namespace s21 {

///@brief Устанавливает конкретную стратегию
///@param concrete_strategy указатель на конктретную стратегию
void AffineTransformations::SetStrategy(Strategy *concrete_strategy) {
  strategy_ = concrete_strategy;
}

/// @brief Изменяет объект в пространстве
/// @param data данные объекта
/// @param point входящая координата
void AffineTransformations::Transformations(
    s21::Data3DModel *data, double point,
    Strategy::TypeCoordinate coordinate_x_y_z) {
  strategy_->Transformations(data, point, coordinate_x_y_z);
}

void MoveObj::Transformations(s21::Data3DModel *data, double point,
                              TypeCoordinate coordinate_x_y_z) {
  for (auto &i : data->GetCoordinateVertex()) {
    if (coordinate_x_y_z == TypeCoordinate::kX) i.x += point;
    if (coordinate_x_y_z == TypeCoordinate::kY) i.y += point;
    if (coordinate_x_y_z == TypeCoordinate::kZ) i.z += point;
  }
}

void RotateObj::Transformations(Data3DModel *data, double point,
                                Strategy::TypeCoordinate coordinate_x_y_z) {
  switch (coordinate_x_y_z) {
    case Strategy::TypeCoordinate::kX:
      Rotate(data, point, &RotateObj::RotateX);
      break;
    case Strategy::TypeCoordinate::kY:
      Rotate(data, point, &RotateObj::RotateY);
      break;
    case Strategy::TypeCoordinate::kZ:
      Rotate(data, point, &RotateObj::RotateZ);
      break;
  }
}

void RotateObj::Rotate(Data3DModel *data, double point,
                       void (RotateObj::*SomeMethod)(Data3DModel::Coordinate &,
                                                     double)) {
  point *= M_PI / 180;
  for (auto &i : data->GetCoordinateVertex()) {
    (this->*SomeMethod)(i, point);
  }
}

void RotateObj::RotateX(Data3DModel::Coordinate &i, double point) {
  double tmp_y = i.y;
  double tmp_z = i.z;
  i.y = tmp_y * cos(point) + tmp_z * sin(point);
  i.z = -tmp_y * sin(point) + tmp_z * cos(point);
}

void RotateObj::RotateY(Data3DModel::Coordinate &i, double point) {
  double tmp_x = i.x;
  double tmp_z = i.z;
  i.x = tmp_x * cos(point) + tmp_z * sin(point);
  i.z = -tmp_x * sin(point) + tmp_z * cos(point);
}

void RotateObj::RotateZ(Data3DModel::Coordinate &i, double point) {
  double tmp_x = i.x;
  double tmp_y = i.y;
  i.x = tmp_x * cos(point) + tmp_y * sin(point);
  i.y = -tmp_x * sin(point) + tmp_y * cos(point);
}

void DistanceObj::Transformations(
    s21::Data3DModel *data, double point,
    s21::Strategy::TypeCoordinate coordinate_x_y_z) {
  if (coordinate_x_y_z == Strategy::TypeCoordinate::kZ) {
    for (auto &i : data->GetCoordinateVertex()) {
      i.x *= point;
      i.y *= point;
      i.z *= point;
    }
  }
}

}  // namespace s21