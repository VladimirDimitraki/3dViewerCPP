#ifndef CPP4_3DVIEWER_V2_VIEW_GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <QtOpenGLWidgets/qopenglwidget.h>

#include <QColor>
#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QWidget>

#include "../Controller/controller.h"

namespace s21 {

class GLWidget : public QOpenGLWidget {
 public:
  enum class LinesType { kSolid, kDashed };
  enum class VertexesType { kNone, kCircle, kSquare };
  enum class ProjectionType { kCentral, kParallel };

  explicit GLWidget(QWidget *parent = nullptr, s21::Controller *c = nullptr);

  void SetDefault();

  void SetLinesType(LinesType type) {
    lines_type_ = type;
    update();
  }

  void SetVertexesType(VertexesType type) {
    vertexes_type_ = type;
    update();
  }

  void SetProjectionType(ProjectionType type) {
    projection_type_ = type;
    update();
  }

  void SetBackgroundColor(QColor color) {
    backround_color_ = color;
    update();
  }
  void SetVertexesColor(QColor color) {
    vertexes_color_ = color;
    update();
  }
  void SetLinesColor(QColor color) {
    lines_color_ = color;
    update();
  }
  void SetVertexesSize(int size) {
    vertex_size_ = size;
    update();
  }
  void SetLinesWidth(int width) {
    line_width_ = width;
    update();
  }

  void SetRotX(double value) { x_rot_ = value; }
  void SetRotY(double value) { y_rot_ = value; }
  void SetRotZ(double value) { z_rot_ = value; }

  void UpdateSumRotX(double value) { sum_rot_x += value; }
  void UpdateSumRotY(double value) { sum_rot_y += value; }
  void UpdateSumRotZ(double value) { sum_rot_z += value; }

  void SetSumRotX(double value) { sum_rot_x = value; }
  void SetSumRotY(double value) { sum_rot_y = value; }
  void SetSumRotZ(double value) { sum_rot_z = value; }

  QColor GetBackgroundColor() { return backround_color_; }
  QColor GetVertexesColor() { return vertexes_color_; }
  QColor GetLinesColor() { return lines_color_; }
  [[nodiscard]] int GetLineWidth() const { return line_width_; }
  [[nodiscard]] int GetVertexSize() const { return vertex_size_; }
  LinesType GetLinesType() { return lines_type_; }
  VertexesType GetVertexesType() { return vertexes_type_; }
  ProjectionType GetProjectionType() { return projection_type_; }
  [[nodiscard]] double GetRotX() const { return x_rot_; }
  [[nodiscard]] double GetRotY() const { return y_rot_; }
  [[nodiscard]] double GetRotZ() const { return z_rot_; }

  [[nodiscard]] double GetSumRotX() const { return sum_rot_x; }
  [[nodiscard]] double GetSumRotY() const { return sum_rot_y; }
  [[nodiscard]] double GetSumRotZ() const { return sum_rot_z; }

  void clearOpenGlWidget();

 private:
  s21::Controller *controller_;
  double x_rot_, y_rot_, z_rot_;
  double sum_rot_x, sum_rot_y, sum_rot_z;
  double aspect_ratio_;
  QPoint m_pos_;

  QColor backround_color_;
  QColor vertexes_color_;
  QColor lines_color_;
  int line_width_;
  int vertex_size_;

  LinesType lines_type_;
  VertexesType vertexes_type_;
  ProjectionType projection_type_;

  void setProjection();
  void drawVertexes();
  void setLinesType();
  void drawLines();

  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int w, int h) override;

  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
};

}  // namespace s21

#define CPP4_3DVIEWER_V2_VIEW_GLWIDGET_H

#endif  // CPP4_3DVIEWER_V2_VIEW_GLWIDGET_H
