#include "CubeWidget.h"
#include <QOpenGLShaderProgram>
#include <QMatrix4x4>

CubeWidget::CubeWidget(QWidget* parent) : QOpenGLWidget(parent), rollAngle(0.0), pitchAngle(0.0), yawAngle(0.0)
{
}

CubeWidget::~CubeWidget()
{
}

void CubeWidget::initializeGL()
{
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void CubeWidget::resizeGL(int w, int h)
{
  glViewport(0, 0, w, h);

  projection.setToIdentity();
  float aspect = float(w) / float(h ? h : 1);

  float size = 2.0f;
  if (w >= h)
  {
    projection.ortho(-size * aspect, size * aspect, -size, size, -100.0f, 100.0f);
  }
  else
  {
    projection.ortho(-size, size, -size / aspect, size / aspect, -100.0f, 100.0f);
  }
}

void CubeWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  QMatrix4x4 modelView;
  modelView.setToIdentity();
  modelView.lookAt(QVector3D(0.0f, 0.0f, 5.0f), QVector3D(0.0f, 0.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

  modelView.rotate(rollAngle, 1.0f, 0.0f, 0.0f);
  modelView.rotate(pitchAngle, 0.0f, 1.0f, 0.0f);
  modelView.rotate(yawAngle, 0.0f, 0.0f, 1.0f);

  QMatrix4x4 mvp = projection * modelView;
  glLoadMatrixf(mvp.constData());

  drawCube();
}

void CubeWidget::drawCube()
{
  glBegin(GL_QUADS);

  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);

  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);

  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);

  glColor3f(1.0f, 1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);

  glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f);

  glColor3f(0.0f, 1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f);
  glVertex3f(1.0f, -1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f);

  glEnd();
}

void CubeWidget::rotateCube(double roll, double pitch, double yaw)
{
  rollAngle = roll;
  pitchAngle = pitch;
  yawAngle = yaw;

  update();
}
