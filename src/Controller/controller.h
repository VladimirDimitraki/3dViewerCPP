#ifndef CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H
#define CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H

#include "../Model/model.h"

namespace s21 {

class Controller {
 public:
  Controller() {}
  Controller(Model *m) : model_(m) {}

  void Affine(Strategy::SelectionStrategy select_strategy,
              Strategy::TypeCoordinate type, Data3DModel *data, double point);
  bool ParseFile(std::string file_path);
  Data3DModel &GetData();
  void SetCentre(Data3DModel *data);

 private:
  Model *model_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_CONTROLLER_CONTROLLER_H
