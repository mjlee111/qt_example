#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QTimer>
#include <QVBoxLayout>
#include <QLayout>

class CubeWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
  Q_OBJECT

public:
  CubeWidget(QWidget* parent = nullptr);
  ~CubeWidget();

  void rotateCube(double roll, double pitch, double yaw);

protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

private:
  void drawCube();
  QMatrix4x4 projection;
  double rollAngle;
  double pitchAngle;
  double yawAngle;
};

#endif  // CUBEWIDGET_H
