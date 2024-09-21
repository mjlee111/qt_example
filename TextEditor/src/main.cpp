#include "texteditor.h"

#include <QApplication>

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);
  Editor w;
  w.setFixedSize(610, 630);
  w.show();
  return a.exec();
}
