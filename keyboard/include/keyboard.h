#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class keyboard; }
QT_END_NAMESPACE

class keyboard : public QMainWindow
{
    Q_OBJECT

public:
    keyboard(QWidget *parent = nullptr);
    ~keyboard();

private:
    Ui::keyboard *ui;
};
#endif // KEYBOARD_H
