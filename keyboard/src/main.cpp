#include "keyboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    keyboard w;
    w.setFixedSize(620, 330);
    w.show();
    return a.exec();
}