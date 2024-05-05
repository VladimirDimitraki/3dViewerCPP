#ifndef CPP4_3DVIEWER_V2_MODEL_AFFINETRANSFORMATIONS_H
#define CPP4_3DVIEWER_V2_MODEL_AFFINETRANSFORMATIONS_H

#include <cmath>

#include "data_3d_model.h"

namespace s21 {
///@brief Абстрактный класс внутри реализован паттерн "Strategy"
///@param TypeCoordinate перечисление для типа координат
///@param SelectionStrategy тип стратегии
class Strategy {
 public:
  enum class TypeCoordinate { kX, kY, kZ };
  enum class SelectionStrategy { kMove, kRotate, kDistance };

  Strategy() = default;
  virtual ~Strategy() = default;

  virtual void Transformations(Data3DModel *data, double point,
                               TypeCoordinate coordinate_x_y_z) = 0;
};

class MoveObj : public Strategy {
  void Transformations(Data3DModel *data, double point,
                       TypeCoordinate coordinate_x_y_z) override;
};

class RotateObj : public Strategy {
  void Transformations(Data3DModel *data, double point,
                       TypeCoordinate coordinate_x_y_z) override;
  void Rotate(Data3DModel *data, double point,
              void (RotateObj::*SomeMethod)(Data3DModel::Coordinate &, double));
  void RotateX(Data3DModel::Coordinate &i, double point);
  void RotateY(Data3DModel::Coordinate &i, double point);
  void RotateZ(Data3DModel::Coordinate &i, double point);
};

class DistanceObj : public Strategy {
  void Transformations(s21::Data3DModel *data, double point,
                       TypeCoordinate coordinate_x_y_z) override;
};

class AffineTransformations {
 public:
  AffineTransformations() = default;
  ~AffineTransformations() = default;

  void SetStrategy(Strategy *concrete_strategy);
  void Transformations(Data3DModel *data, double point,
                       Strategy::TypeCoordinate coordinate_x_y_z);

 private:
  Strategy *strategy_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_AFFINETRANSFORMATIONS_H