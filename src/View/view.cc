#include "view.h"

#include "ui_mainwindow.h"

namespace s21 {

View::View(QWidget *parent, s21::Controller *controller)
    : QMainWindow(parent), ui_(new Ui::View), controller_(controller) {
  ui_->setupUi(this);
  setWindowTitle("3D Viewer");
  gif_timer_ = new QTimer(nullptr);
  controller_->GetData().ClearData();
  gl_widget_ = new GLWidget(nullptr, controller);
  ui_->layoutForGl->addWidget(gl_widget_);
  ui_->centralwidget->setSizePolicy(QSizePolicy::Expanding,
                                    QSizePolicy::Expanding);

  setCentralWidget(ui_->centralwidget);

  connect(ui_->OpenFilePushButtonClicked, SIGNAL(clicked()), this,
          SLOT(OpenFilePushButtonClicked()));
  connect(ui_->CleanPushButtonClicked, SIGNAL(clicked()), this,
          SLOT(CleanPushButtonClicked()));
  connect(ui_->SetBckgColorClicked, SIGNAL(clicked()), this,
          SLOT(SetBckgColorClicked()));
  connect(ui_->SetLinesColorClicked, SIGNAL(clicked()), this,
          SLOT(SetLinesColorClicked()));
  connect(ui_->SetVertexesColorClicked, SIGNAL(clicked()), this,
          SLOT(SetVertexesColorClicked()));

  connect(ui_->projectionType, SIGNAL(currentIndexChanged(int)), this,
          SLOT(ProjectionTypeChanged(int)));
  connect(ui_->linesType, SIGNAL(currentIndexChanged(int)), this,
          SLOT(LinesTypeChanged(int)));
  connect(ui_->VertexesType, SIGNAL(currentIndexChanged(int)), this,
          SLOT(VertexesTypeChanged(int)));

  connect(ui_->lineSizeEditer, SIGNAL(valueChanged(int)), this,
          SLOT(LinesWidthValueChanged(int)));
  connect(ui_->vertexSizeEditer, SIGNAL(valueChanged(int)), this,
          SLOT(VertexSizeValueChanged(int)));

  connect(gif_timer_, SIGNAL(timeout()), this, SLOT(CreateAnimation()));
  connect(ui_->createScreenPshBtn, SIGNAL(clicked()), this,
          SLOT(CreateScreenClicked()));
  connect(ui_->createGifPshBtn, SIGNAL(clicked()), this,
          SLOT(CreateGifClicked()));

  connect(ui_->ButtonPlusMoveZ, SIGNAL(clicked()), this,
          SLOT(ButtonPlusMoveZ()));
  connect(ui_->ButtonMinusMoveZ, SIGNAL(clicked()), this,
          SLOT(ButtonMinusMoveZ()));
  connect(ui_->ButtonPlusMoveY, SIGNAL(clicked()), this,
          SLOT(ButtonPlusMoveY()));
  connect(ui_->ButtonMinusMoveY, SIGNAL(clicked()), this,
          SLOT(ButtonMinusMoveY()));
  connect(ui_->ButtonPlusMoveX, SIGNAL(clicked()), this,
          SLOT(ButtonPlusMoveX()));
  connect(ui_->ButtonMinusMoveX, SIGNAL(clicked()), this,
          SLOT(ButtonMinusMoveX()));

  connect(ui_->ButtonRotatePlusX, SIGNAL(clicked()), this,
          SLOT(ButtonRotatePlusX()));
  connect(ui_->ButtonRotateMinusX, SIGNAL(clicked()), this,
          SLOT(ButtonRotateMinusX()));
  connect(ui_->ButtonRotatePlusY, SIGNAL(clicked()), this,
          SLOT(ButtonRotatePlusY()));
  connect(ui_->ButtonRotateMinusY, SIGNAL(clicked()), this,
          SLOT(ButtonRotateMinusY()));
  connect(ui_->ButtonRotatePlusZ, SIGNAL(clicked()), this,
          SLOT(ButtonRotatePlusZ()));
  connect(ui_->ButtonRotateMinusZ, SIGNAL(clicked()), this,
          SLOT(ButtonRotateMinusZ()));

  connect(ui_->ButtonPlusSize, SIGNAL(clicked()), this, SLOT(ButtonPlusSize()));
  connect(ui_->ButtonMinusSize, SIGNAL(clicked()), this,
          SLOT(ButtonMinusSize()));

  connect(ui_->SetDefaultButton, SIGNAL(clicked()), this,
          SLOT(SetDefaultButton()));
  gl_widget_->SetDefault();
  readSettings();
}

View::~View() {
  writeSettings();
  delete gif_timer_;
  delete ui_;
  delete gl_widget_;
}

void View::OpenFilePushButtonClicked() {
  file_path_ = QFileDialog::getOpenFileName(this, "Выбрать файл", "/Users",
                                            "All Files (*.obj)");
  ui_->vertexCount->setText("");
  ui_->polygonCount->setText("");
  ui_->fileNameLabel->setText("");
  controller_->GetData().ClearData();
  std::string std_string = file_path_.toStdString();
  if (controller_->ParseFile(std_string)) {
    ui_->vertexCount->setText(
        QString::number(controller_->GetData().GetCoordinateVertex().size()));
    ui_->polygonCount->setText(
        QString::number(controller_->GetData().GetStringPolygon().size() / 2));
    QFileInfo check_file(file_path_);
    ui_->fileNameLabel->setText(check_file.fileName());
    controller_->SetCentre(&controller_->GetData());
    gl_widget_->update();
  }
}

void View::SetBckgColorClicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
  gl_widget_->SetBackgroundColor(color);
  gl_widget_->update();
}

void View::SetLinesColorClicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
  gl_widget_->SetLinesColor(color);
  gl_widget_->update();
}

void View::SetVertexesColorClicked() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select color:");
  gl_widget_->SetVertexesColor(color);
  gl_widget_->update();
}

void View::CleanPushButtonClicked() {
  file_path_ = "";
  SetDefaultButton();
  ui_->fileNameLabel->setText("");
  ui_->polygonCount->setText("");
  ui_->vertexCount->setText("");
  gl_widget_->clearOpenGlWidget();
  controller_->GetData().ClearData();
}

void View::SetDefaultButton() {
  gl_widget_->SetDefault();
  ui_->lineSizeEditer->setValue(1);
  ui_->vertexSizeEditer->setValue(0);
  ui_->projectionType->setCurrentIndex(0);
  ui_->VertexesType->setCurrentIndex(0);
  ui_->linesType->setCurrentIndex(0);

  ui_->ROTATE_X_VALUE->setValue(0);
  ui_->ROTATE_Y_VALUE->setValue(0);
  ui_->ROTATE_Z_VALUE->setValue(0);

  ui_->doubleSpinBox_X_MOVE->setValue(0);
  ui_->doubleSpinBox_Y_MOVE->setValue(0);
  ui_->doubleSpinBox_MOVE_Z->setValue(0);

  controller_->SetCentre(&controller_->GetData());
  gl_widget_->update();
}

void View::ProjectionTypeChanged(int index) {
  if (index == 0) {
    gl_widget_->SetProjectionType(GLWidget::ProjectionType::kCentral);
  } else if (index == 1) {
    gl_widget_->SetProjectionType(GLWidget::ProjectionType::kParallel);
  }
}

void View::LinesTypeChanged(int index) {
  if (index == 0) {
    gl_widget_->SetLinesType(GLWidget::LinesType::kSolid);
  } else if (index == 1) {
    gl_widget_->SetLinesType(GLWidget::LinesType::kDashed);
  }
}

void View::VertexesTypeChanged(int index) {
  if (index == 0) {
    gl_widget_->SetVertexesType(GLWidget::VertexesType::kNone);
  } else if (index == 1) {
    gl_widget_->SetVertexesType(GLWidget::VertexesType::kCircle);
  } else if (index == 2) {
    gl_widget_->SetVertexesType(GLWidget::VertexesType::kSquare);
  }
}

void View::VertexSizeValueChanged(int value) {
  gl_widget_->SetVertexesSize(value);
  update();
}

void View::LinesWidthValueChanged(int value) {
  gl_widget_->SetLinesWidth(value);
  update();
}

void View::writeSettings() {
  QString pathSettings = QCoreApplication::applicationDirPath();
  QSettings settings(pathSettings + "/settings.ini", QSettings::IniFormat);
  settings.beginGroup("settings");

  settings.setValue("file_path_", file_path_);
  settings.setValue("backgroundColor", gl_widget_->GetBackgroundColor());
  settings.setValue("lines_color_", gl_widget_->GetLinesColor());
  settings.setValue("vertexes_color_", gl_widget_->GetVertexesColor());
  settings.setValue("lineSizeEditer", ui_->lineSizeEditer->value());
  settings.setValue("lineWidth", gl_widget_->GetLineWidth());
  settings.setValue("vertexSize", gl_widget_->GetVertexSize());
  settings.setValue("vertexSizeEditer", ui_->vertexSizeEditer->value());

  settings.setValue("VertexesType", ui_->VertexesType->currentIndex());
  settings.setValue("linesType", ui_->linesType->currentIndex());
  settings.setValue("projectionType", ui_->projectionType->currentIndex());

  settings.setValue("lineType", static_cast<int>(gl_widget_->GetLinesType()));
  settings.setValue("vertexType",
                    static_cast<int>(gl_widget_->GetVertexesType()));
  settings.setValue("projection",
                    static_cast<int>(gl_widget_->GetProjectionType()));

  settings.setValue("x_rot_", gl_widget_->GetRotX());
  settings.setValue("y_rot_", gl_widget_->GetRotY());
  settings.setValue("z_rot_", gl_widget_->GetRotZ());

  settings.endGroup();
}

void View::readSettings() {
  QString pathSettings = QCoreApplication::applicationDirPath();
  QSettings settings(pathSettings + "/settings.ini", QSettings::IniFormat);
  settings.beginGroup("settings");

  file_path_ = settings.value("file_path_", "").toString();

  QFileInfo check_file(file_path_);

  controller_->GetData().ClearData();
  std::string std_string = file_path_.toStdString();
  if (controller_->ParseFile(std_string)) {
    ui_->vertexCount->setText(
        QString::number(controller_->GetData().GetCoordinateVertex().size()));
    ui_->polygonCount->setText(
        QString::number(controller_->GetData().GetStringPolygon().size() / 2));
    ui_->fileNameLabel->setText(check_file.fileName());
    controller_->SetCentre(&controller_->GetData());
  }

  gl_widget_->SetBackgroundColor(
      QColor(settings.value("backgroundColor", QColor(Qt::black)).toString()));
  gl_widget_->SetLinesColor(
      QColor(settings.value("lines_color_", QColor(Qt::white)).toString()));
  gl_widget_->SetVertexesColor(
      QColor(settings.value("vertexes_color_", QColor(Qt::white)).toString()));

  ui_->lineSizeEditer->setValue(settings.value("lineSizeEditer", 1).toInt());
  gl_widget_->SetLinesWidth(settings.value("lineWidth", 1).toInt());

  ui_->vertexSizeEditer->setValue(
      settings.value("vertexSizeEditer", 1).toInt());
  gl_widget_->SetVertexesSize(settings.value("vertexSize", 1).toInt());

  ui_->VertexesType->setCurrentIndex(settings.value("VertexesType", 0).toInt());
  ui_->linesType->setCurrentIndex(settings.value("linesType", 0).toInt());
  ui_->projectionType->setCurrentIndex(
      settings.value("projectionType", 0).toInt());

  gl_widget_->SetLinesType(static_cast<GLWidget::LinesType>(
      settings.value("lineType", static_cast<int>(GLWidget::LinesType::kSolid))
          .toInt()));
  gl_widget_->SetVertexesType(static_cast<GLWidget::VertexesType>(
      settings
          .value("vertexType", static_cast<int>(GLWidget::VertexesType::kNone))
          .toInt()));
  gl_widget_->SetProjectionType(static_cast<GLWidget::ProjectionType>(
      settings
          .value("projection",
                 static_cast<int>(GLWidget::ProjectionType::kCentral))
          .toInt()));

  gl_widget_->SetRotX(settings.value("x_rot_", 0).toInt());
  gl_widget_->SetRotY(settings.value("y_rot_", 0).toInt());
  gl_widget_->SetRotZ(settings.value("z_rot_", 0).toInt());

  settings.endGroup();
  gl_widget_->update();
}

void View::ButtonPlusMoveZ() {
  double value = ui_->doubleSpinBox_MOVE_Z->value();
  controller_->Affine(Strategy::SelectionStrategy::kMove,
                      Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                      value);
  gl_widget_->update();
}

void View::ButtonMinusMoveZ() {
  double value = ui_->doubleSpinBox_MOVE_Z->value();
  controller_->Affine(Strategy::SelectionStrategy::kMove,
                      Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                      -value);
  gl_widget_->update();
}

void View::ButtonPlusMoveY() {
  double value = ui_->doubleSpinBox_Y_MOVE->value();
  controller_->Affine(Strategy::SelectionStrategy::kMove,
                      Strategy::TypeCoordinate::kY, &controller_->GetData(),
                      value);
  gl_widget_->update();
}

void View::ButtonMinusMoveY() {
  double value = ui_->doubleSpinBox_Y_MOVE->value();
  controller_->Affine(Strategy::SelectionStrategy::kMove,
                      Strategy::TypeCoordinate::kY, &controller_->GetData(),
                      -value);
  gl_widget_->update();
}

void View::ButtonPlusMoveX() {
  double value = ui_->doubleSpinBox_X_MOVE->value();
  controller_->Affine(Strategy::SelectionStrategy::kMove,
                      Strategy::TypeCoordinate::kX, &controller_->GetData(),
                      value);
  gl_widget_->update();
}

void View::ButtonMinusMoveX() {
  double value = ui_->doubleSpinBox_X_MOVE->value();
  controller_->Affine(Strategy::SelectionStrategy::kMove,
                      Strategy::TypeCoordinate::kX, &controller_->GetData(),
                      -value);
  gl_widget_->update();
}

void View::ButtonPlusSize() {
  double value = 1.1;
  controller_->Affine(Strategy::SelectionStrategy::kDistance,
                      Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                      value);
  gl_widget_->update();
}

void View::ButtonMinusSize() {
  double value = 0.9;
  controller_->Affine(Strategy::SelectionStrategy::kDistance,
                      Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                      value);
  gl_widget_->update();
}

void View::ButtonRotatePlusX() {
  int value = ui_->ROTATE_X_VALUE->value();
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kX, &controller_->GetData(),
                      static_cast<double>(value));
  gl_widget_->UpdateSumRotX(value);
  gl_widget_->update();
}

void View::ButtonRotateMinusX() {
  int value = ui_->ROTATE_X_VALUE->value();
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kX, &controller_->GetData(),
                      static_cast<double>(-value));
  gl_widget_->UpdateSumRotX(-value);
  gl_widget_->update();
}

void View::ButtonRotatePlusY() {
  int value = ui_->ROTATE_Y_VALUE->value();
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kY, &controller_->GetData(),
                      static_cast<double>(value));
  gl_widget_->UpdateSumRotY(value);
  gl_widget_->update();
}

void View::ButtonRotateMinusY() {
  int value = ui_->ROTATE_Y_VALUE->value();
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kY, &controller_->GetData(),
                      static_cast<double>(-value));
  gl_widget_->UpdateSumRotY(-value);
  gl_widget_->update();
}

void View::ButtonRotatePlusZ() {
  int value = ui_->ROTATE_Z_VALUE->value();
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                      static_cast<double>(value));
  gl_widget_->UpdateSumRotZ(value);
  gl_widget_->update();
}

void View::ButtonRotateMinusZ() {
  int value = ui_->ROTATE_Z_VALUE->value();
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                      static_cast<double>(-value));
  gl_widget_->UpdateSumRotZ(-value);
  gl_widget_->update();
}

void View::CreateScreenClicked() {
  QString file_name =
      QFileDialog::getSaveFileName(this, "Сохранить скриншот", "/Users",
                                   "Images (*.jpeg *.bmp);;All Files (*)");
  if (!file_name.isEmpty()) {
    QImage screen = gl_widget_->grabFramebuffer();
    screen.save(file_name);
    QMessageBox success_msg;
    success_msg.setText("Printscreen saved successfully!");
    success_msg.exec();
  } else {
    QMessageBox::warning(this, "", "Printscreen creating failed!");
  }
}

void View::CreateGifClicked() {
  gif_name_ = QFileDialog::getSaveFileName(this, "Save gif", "/Users",
                                           "Gif (*.gif);;All Files (*)");
  if (!gif_name_.isEmpty() && !screen_counter_) {
    gif_frame_ = new QGifImage;
    gif_frame_->setDefaultDelay(10);
    gif_timer_->setInterval(100);
    gif_timer_->start();
    ui_->createGifPshBtn->setEnabled(false);
  } else {
    QMessageBox::warning(this, "", "Gif creating failed!");
  }
}

void View::CreateAnimation() {
  if (screen_counter_ < 50) {
    QImage screen = gl_widget_->grabFramebuffer();
    gif_frame_->addFrame(screen);
    screen_counter_++;
    ui_->createGifPshBtn->setText(QString::number(screen_counter_ / 10, 10));
  } else {
    QMessageBox success_msg;
    success_msg.setText("Gif saved successfully!");
    success_msg.exec();
    gif_timer_->stop();
    screen_counter_ = 0;
    gif_frame_->save(gif_name_);
    delete gif_frame_;
    ui_->createGifPshBtn->setText("Create gif");
    ui_->createGifPshBtn->setEnabled(true);
  }
}

}  // namespace s21
