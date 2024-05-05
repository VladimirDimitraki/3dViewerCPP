#ifndef CPP4_3DVIEWER_V2_MODEL_MODEL_H
#define CPP4_3DVIEWER_V2_MODEL_MODEL_H

#include <iostream>
#include <string>

#include "affine_transformations.h"
#include "data_3d_model.h"
#include "parse_obj.h"
#include "set_centre.h"

namespace s21 {

///@brief Главный класс который реализован по паттерну "Фасад"
class Model {
 public:
  Model();
  ~Model();

  Data3DModel &GetData();
  bool ProccessingObjFile(std::string &file_path);
  void Affine(Strategy::SelectionStrategy select_strategy,
              Strategy::TypeCoordinate type, Data3DModel *data, double point);

  void SetCentre(Data3DModel *data);
  void GiveCommand(Data3DModel *data, Event *event, Event::Command command);

 private:
  Data3DModel data_{};
  ParseObj parse_{};
  AffineTransformations affine_{};
  Strategy *move_obj_;
  Strategy *rotate_obj_;
  Strategy *distance_obj_;
  FindMinMax *find_min_max_;
  FindMax *find_max_;
  FindCentre *find_centre_;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_DATA3DMODEL_H
