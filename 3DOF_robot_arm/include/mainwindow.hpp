#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>
#include <iostream>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui
{
class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow
{
  Q_OBJECT

public:
  mainwindow(QWidget* parent = nullptr);
  ~mainwindow();

private slots:
  void on_generate_clicked();
  void on_reset_clicked();
  void on_joint1_valueChanged(int value);
  void on_joint2_valueChanged(int value);
  void on_joint3_valueChanged(int value);

private:
  Ui::mainwindow* ui;

  QGraphicsScene* scene;
  int link[3] = {
    0,
  };
  int angle[3] = {
    0,
  };

  void drawArm();
};
#endif  // MAINWINDOW_HPP
