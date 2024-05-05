#include <QApplication>

#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::Model m;
  s21::Controller c(&m);
  s21::View w(nullptr, &c);

  w.show();
  return a.exec();
}
