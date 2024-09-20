#include "./ui_mainwindow.h"
#include "mainwindow.hpp"

mainwindow::mainwindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::mainwindow)
{
  ui->setupUi(this);
  QIcon icon(":/image/images/icon.png");
  setWindowIcon(icon);

  scene = new QGraphicsScene(this);
  ui->armGraphics->setScene(scene);
}

mainwindow::~mainwindow()
{
  delete ui;
}

void mainwindow::drawArm()
{
  scene->clear();

  QPointF origin(270, 270);
  QPointF joint1, joint2, endEffector;

  joint1.setX(origin.x() + link[0] * qCos(qDegreesToRadians(static_cast<double>(angle[0]))));
  joint1.setY(origin.y() + link[0] * qSin(qDegreesToRadians(static_cast<double>(angle[0]))));

  joint2.setX(joint1.x() + link[1] * qCos(qDegreesToRadians(static_cast<double>(angle[0] + angle[1]))));
  joint2.setY(joint1.y() + link[1] * qSin(qDegreesToRadians(static_cast<double>(angle[0] + angle[1]))));

  endEffector.setX(joint2.x() + link[2] * qCos(qDegreesToRadians(static_cast<double>(angle[0] + angle[1] + angle[2]))));
  endEffector.setY(joint2.y() + link[2] * qSin(qDegreesToRadians(static_cast<double>(angle[0] + angle[1] + angle[2]))));

  scene->addLine(origin.x(), origin.y(), joint1.x(), joint1.y(), QPen(Qt::white));
  scene->addLine(joint1.x(), joint1.y(), joint2.x(), joint2.y(), QPen(Qt::white));
  scene->addLine(joint2.x(), joint2.y(), endEffector.x(), endEffector.y(), QPen(Qt::white));

  scene->addEllipse(joint1.x() - 3, joint1.y() - 3, 6, 6, QPen(Qt::blue), QBrush(Qt::blue));
  scene->addEllipse(joint2.x() - 3, joint2.y() - 3, 6, 6, QPen(Qt::blue), QBrush(Qt::blue));
  scene->addEllipse(endEffector.x() - 3, endEffector.y() - 3, 6, 6, QPen(Qt::red), QBrush(Qt::red));
}

void mainwindow::on_generate_clicked()
{
  link[0] = ui->link1->value();
  link[1] = ui->link2->value();
  link[2] = ui->link3->value();
  drawArm();
}

void mainwindow::on_reset_clicked()
{
  for (int i = 0; i < 3; i++)
  {
    link[i] = 0;
    angle[i] = 0;
  }
  ui->joint1->setValue(0);
  ui->joint2->setValue(0);
  ui->joint3->setValue(0);

  ui->link1->setValue(0);
  ui->link2->setValue(0);
  ui->link3->setValue(0);

  drawArm();
}

void mainwindow::on_joint1_valueChanged(int value)
{
  angle[0] = value;
  ui->joint1_val->setText(QString::number(value));
  drawArm();
}

void mainwindow::on_joint2_valueChanged(int value)
{
  angle[1] = value;
  ui->joint2_val->setText(QString::number(value));
  drawArm();
}

void mainwindow::on_joint3_valueChanged(int value)
{
  angle[2] = value;
  ui->joint3_val->setText(QString::number(value));
  drawArm();
}
