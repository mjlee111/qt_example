#include "keyboard.h"
#include "ui_keyboard.h"

keyboard::keyboard(QWidget* parent) : QMainWindow(parent), ui(new Ui::keyboard)
{
  ui->setupUi(this);
}

keyboard::~keyboard()
{
  delete ui;
}
