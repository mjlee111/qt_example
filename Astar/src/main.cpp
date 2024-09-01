#include "mainwindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  mainwindow w;
  w.setFixedSize(800, 620);
  w.show();
  return a.exec();
}
