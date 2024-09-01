#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "AstarImpl.hpp"
#include <QGridLayout>
#include <QMainWindow>
#include <QMessageBox>
#include <QPoint>
#include <QPushButton>
#include <QVector>
#include <iostream>


QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow;
}
QT_END_NAMESPACE

class mainwindow : public QMainWindow {
  Q_OBJECT

public:
  mainwindow(QWidget *parent = nullptr);
  ~mainwindow();

private slots:
  void on_generate_clicked();
  void on_set_start_clicked();
  void on_set_end_clicked();
  void on_astar_start_clicked();
  void on_reset_clicked();

private:
  Ui::mainwindow *ui;

  QVector<QVector<int>> map; // 0: empty, 1: obstacle, 2: start, 3: end
  QPoint startPoint;
  QPoint endPoint;

  void initializeMap(int rows, int cols);
  void drawGrid(int rows, int cols);
  void replacePoint(int pointType, int newRow, int newCol,
                    const QString &color);
  void findPath();

  bool isSetStart = false;
  bool isSetEnd = false;
};
#endif // MAINWINDOW_HPP
