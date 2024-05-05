#include "glwidget.h"

namespace s21 {

GLWidget::GLWidget(QWidget *parent, s21::Controller *c)
    : QOpenGLWidget(parent), controller_(c) {
  SetDefault();
}

void GLWidget::SetDefault() {
  projection_type_ = ProjectionType::kCentral;
  vertexes_type_ = VertexesType::kNone;
  lines_type_ = LinesType::kSolid;
  backround_color_ = QColor(Qt::black);
  lines_color_ = QColor(Qt::white);
  vertexes_color_ = QColor(Qt::white);
  line_width_ = 1;
  vertex_size_ = 1;

  x_rot_ = 0;
  y_rot_ = 0;
  z_rot_ = 0;

  update();
}

void GLWidget::initializeGL() {
  glClearColor(backround_color_.redF(), backround_color_.greenF(),
               backround_color_.blueF(), backround_color_.alphaF());
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glClearColor(backround_color_.redF(), backround_color_.greenF(),
               backround_color_.blueF(), backround_color_.alphaF());
  glTranslated(0, 0, -10);
  setProjection();
  drawVertexes();
  setLinesType();
  drawLines();
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  aspect_ratio_ = qreal(w) / qreal(h ? h : 1);
}

void GLWidget::setLinesType() {
  if (lines_type_ == LinesType::kDashed) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  if (!lines_color_.isValid()) {
    lines_color_ = QColor(Qt::white);
  } else {
    glColor3f(lines_color_.redF(), lines_color_.greenF(), lines_color_.blueF());
  }
  glLineWidth(line_width_);
}

void GLWidget::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection_type_ == ProjectionType::kParallel) {
    glOrtho(-2 * aspect_ratio_, 2 * aspect_ratio_, -2, 2, 0.1, 100);
  } else if (projection_type_ == ProjectionType::kCentral) {
    gluPerspective(24, aspect_ratio_, 0.1, 100);
  }
  glMatrixMode(GL_MODELVIEW);
}

void GLWidget::drawVertexes() {
  if (vertexes_type_ == VertexesType::kCircle) {
    glEnable(GL_POINT_SMOOTH);
  } else if (vertexes_type_ == VertexesType::kSquare) {
    glEnable(GL_POINT_SPRITE);
  }

  if (vertexes_type_ != VertexesType::kNone) {
    if (!vertexes_color_.isValid()) {
      vertexes_color_ = QColor(Qt::white);
    } else {
      glColor3f(vertexes_color_.redF(), vertexes_color_.greenF(),
                vertexes_color_.blueF());
    }
    glPointSize(static_cast<GLfloat>(vertex_size_));

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0,
                    controller_->GetData().GetCoordinateVertex().data());
    glDrawElements(GL_POINTS, controller_->GetData().GetStringPolygon().size(),
                   GL_UNSIGNED_INT,
                   controller_->GetData().GetStringPolygon().data());
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  if (vertexes_type_ == VertexesType::kCircle) {
    glDisable(GL_POINT_SMOOTH);
  } else if (vertexes_type_ == VertexesType::kSquare) {
    glDisable(GL_POINT_SPRITE);
  }
}

void GLWidget::drawLines() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_DOUBLE, 0,
                  controller_->GetData().GetCoordinateVertex().data());
  glDrawElements(GL_LINES, controller_->GetData().GetStringPolygon().size(),
                 GL_UNSIGNED_INT,
                 controller_->GetData().GetStringPolygon().data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::clearOpenGlWidget() {
  makeCurrent();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  doneCurrent();
  update();
}

void GLWidget::mousePressEvent(QMouseEvent *mo) { m_pos_ = mo->pos(); }

void GLWidget::mouseMoveEvent(QMouseEvent *mo) {
  const float sense = 0.3f;

  x_rot_ = sense * (mo->pos().y() - m_pos_.y());
  y_rot_ = sense * (mo->pos().x() - m_pos_.x());
  m_pos_ = mo->pos();

  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kX, &controller_->GetData(),
                      -x_rot_);
  sum_rot_x += x_rot_;
  controller_->Affine(Strategy::SelectionStrategy::kRotate,
                      Strategy::TypeCoordinate::kY, &controller_->GetData(),
                      y_rot_);
  sum_rot_y += y_rot_;
  update();
}

void GLWidget::wheelEvent(QWheelEvent *event) {
  const float scaleFactor = 0.9f;

  if (event->angleDelta().y() > 0) {
    controller_->Affine(Strategy::SelectionStrategy::kDistance,
                        Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                        scaleFactor);
  } else {
    controller_->Affine(Strategy::SelectionStrategy::kDistance,
                        Strategy::TypeCoordinate::kZ, &controller_->GetData(),
                        1.0f / scaleFactor);
  }
  update();
}

}  // namespace s21
