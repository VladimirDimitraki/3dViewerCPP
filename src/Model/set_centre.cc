#include "set_centre.h"

namespace s21 {
///Создаем цепочку обязанностей
///@param event событие которое обрабатывает определенную стадию центровки
Event *AbstructEvent::SetNextEvent(Event *event) {
  next_event_ = event;
  return event;
}

void FindMax::Update(s21::Event *e) {
  min_ = e->min_;
  max_ = e->max_;
  centre_ = e->centre_;
  scale_for_centre_ = e->scale_for_centre_;
}

void FindCentre::Update(s21::Event *e) {
  min_ = e->min_;
  max_ = e->max_;
  centre_ = e->centre_;
  scale_for_centre_ = e->scale_for_centre_;
}

Event::VerifyExecution FindMinMax::Execute(s21::Data3DModel *data,
                                           Command command) {
  auto v = data->GetCoordinateVertex().begin();
  InitMinMax(*v);
  if (command == Event::Command::kFindMinMax) {
    for (auto &vertex : data->GetCoordinateVertex()) {
      if (min_.x >= vertex.x)
        min_.x = vertex.x;
      else if (max_.x <= vertex.x)
        max_.x = vertex.x;

      if (min_.y >= vertex.y)
        min_.y = vertex.y;
      else if (max_.y <= vertex.y)
        max_.y = vertex.y;

      if (min_.z >= vertex.z)
        min_.z = vertex.z;
      else if (max_.z <= vertex.z)
        max_.z = vertex.z;
    }

    centre_.x = min_.x + (max_.x - min_.x) / 2;
    centre_.y = min_.y + (max_.y - min_.y) / 2;
    centre_.z = min_.z + (max_.z - min_.z) / 2;
  }
  return VerifyExecution::kExecution;
}

void FindMinMax::InitMinMax(Data3DModel::Coordinate &vertex) {
  min_.x = vertex.x;
  min_.y = vertex.y;
  min_.z = vertex.z;
  max_.x = vertex.x;
  max_.y = vertex.y;
  max_.z = vertex.z;
}

Event::VerifyExecution FindMax::Execute(s21::Data3DModel *data,
                                        Command command) {
  data->GetCoordinateVertex();
  if (command == Event::Command::kFindMax) {
    double x = max_.x - min_.x, y = max_.y - min_.y, z = max_.z - min_.z;
    if (x >= y && y >= z) {
      scale_for_centre_ = x;
    } else if (y >= x && x >= z) {
      scale_for_centre_ = y;
    } else {
      scale_for_centre_ = z;
    }
  }
  return VerifyExecution::kExecution;
}

Event::VerifyExecution FindCentre::Execute(s21::Data3DModel *data,
                                           Command command) {
  if (command == Event::Command::kFindCentre) {
    double scale = (1 - (1 * (-1))) / scale_for_centre_;
    for (auto &vertex : data->GetCoordinateVertex()) {
      vertex.x -= centre_.x;
      vertex.x *= scale;
      vertex.y -= centre_.y;
      vertex.y *= scale;
      vertex.z -= centre_.z;
      vertex.z *= scale;
    }
  }
  return VerifyExecution::kExecution;
}

}  // namespace s21