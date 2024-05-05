#ifndef CPP4_3DVIEWER_V2_MODEL_SETCENTRE_H
#define CPP4_3DVIEWER_V2_MODEL_SETCENTRE_H

#include <istream>

#include "data_3d_model.h"

namespace s21 {

///@brief Главный интерфейс реализован по паттерну "Chain of responsibility"
class Event {
 public:
  enum class VerifyExecution { kExecution, kNotExecution };
  enum class Command { kFindMinMax, kFindMax, kFindCentre };
  struct MinMax {
    MinMax() : x(0), y(0), z(0) {}
    double x, y, z;
  };
  Event() = default;
  virtual ~Event() = default;

  ///Передает обязанности следующему по цепочке
  ///@param data данные 3d модели
  virtual Event *SetNextEvent(Event *event) = 0;

  /// Принимает комманду на исполнение
  ///@return VerifyExecutionу успешное выполнение
  virtual VerifyExecution Execute(Data3DModel *data, Command command) = 0;

  double scale_for_centre_;
  MinMax centre_;
  MinMax min_;
  MinMax max_;
};

class AbstructEvent : public Event {
 public:
  AbstructEvent() : next_event_(nullptr) {}
  Event *SetNextEvent(Event *event) override;

 private:
  Event *next_event_;
};

class FindMinMax : public AbstructEvent {
 public:
  VerifyExecution Execute(Data3DModel *data, Command command) override;
  void InitMinMax(Data3DModel::Coordinate &vertex);
};

class FindMax : public AbstructEvent {
 public:
  void Update(Event *e);

  VerifyExecution Execute(Data3DModel *data, Command command) override;
};

class FindCentre : public AbstructEvent {
 public:
  void Update(Event *e);

  VerifyExecution Execute(Data3DModel *data, Command command) override;
};

}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_MODEL_SETCENTRE_H