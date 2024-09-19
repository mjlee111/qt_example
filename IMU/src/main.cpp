#include "IMU.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  IMU w;
  w.setFixedSize(1210, 630);
  w.show();
  return a.exec();
}
