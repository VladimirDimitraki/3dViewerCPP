#include "controller.h"

namespace s21 {

bool Controller::ParseFile(std::string file_path) {
  return model_->ProccessingObjFile(file_path);
}

void Controller::SetCentre(s21::Data3DModel *data) { model_->SetCentre(data); }

Data3DModel &Controller::GetData() { return model_->GetData(); }

void Controller::Affine(Strategy::SelectionStrategy select_strategy,
                        Strategy::TypeCoordinate type, Data3DModel *data,
                        double point) {
  model_->Affine(select_strategy, type, data, point);
}

}  // namespace s21