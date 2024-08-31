#include "serial.h"

#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  Serial w;
  w.setFixedSize(590, 600);
  w.show();
  return a.exec();
}
