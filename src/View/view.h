#ifndef CPP4_3DVIEWER_V2_VIEW_VIEW_H
#define CPP4_3DVIEWER_V2_VIEW_VIEW_H

#include <QColorDialog>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QVBoxLayout>

#include "../Controller/controller.h"
#include "QtGifImage/gifimage/qgifimage.h"
#include "glwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr,
                s21::Controller *controller = nullptr);
  ~View() override;

  void writeSettings();
  void readSettings();

 private slots:
  void OpenFilePushButtonClicked();
  void SetBckgColorClicked();
  void SetLinesColorClicked();
  void SetVertexesColorClicked();

  void ProjectionTypeChanged(int index);
  void LinesTypeChanged(int index);
  void VertexesTypeChanged(int index);

  void VertexSizeValueChanged(int value);
  void LinesWidthValueChanged(int value);

  void ButtonPlusMoveZ();
  void ButtonMinusMoveZ();
  void ButtonPlusMoveY();
  void ButtonMinusMoveY();
  void ButtonPlusMoveX();
  void ButtonMinusMoveX();

  void ButtonPlusSize();
  void ButtonMinusSize();

  void ButtonRotatePlusX();
  void ButtonRotateMinusX();
  void ButtonRotatePlusY();
  void ButtonRotateMinusY();
  void ButtonRotatePlusZ();
  void ButtonRotateMinusZ();

  void SetDefaultButton();
  void CleanPushButtonClicked();

  void CreateAnimation();
  void CreateScreenClicked();
  void CreateGifClicked();

 private:
  Ui::View *ui_;
  s21::Controller *controller_;
  GLWidget *gl_widget_;
  QString file_path_;
  QString gif_name_;
  QGifImage *gif_frame_;
  int screen_counter_ = 0;
  QTimer *gif_timer_;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_VIEW_VIEW_H
