/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwindow
{
public:
    QWidget *centralwidget;
    QSpinBox *link1;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *link2;
    QPushButton *generate;
    QPushButton *reset;
    QLabel *copyright;
    QLabel *label_3;
    QSpinBox *link3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QSlider *joint1;
    QLabel *joint1_val;
    QLabel *joint2_val;
    QSlider *joint2;
    QLabel *joint3_val;
    QSlider *joint3;
    QGraphicsView *armGraphics;

    void setupUi(QMainWindow *mainwindow)
    {
        if (mainwindow->objectName().isEmpty())
            mainwindow->setObjectName(QString::fromUtf8("mainwindow"));
        mainwindow->resize(780, 630);
        mainwindow->setStyleSheet(QString::fromUtf8("background-color: rgb(72, 72, 72);\n"
"color: rgb(255, 255, 255)"));
        centralwidget = new QWidget(mainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        link1 = new QSpinBox(centralwidget);
        link1->setObjectName(QString::fromUtf8("link1"));
        link1->setGeometry(QRect(600, 10, 170, 25));
        link1->setMinimum(1);
        link1->setMaximum(30);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(560, 10, 40, 25));
        label->setFrameShape(QFrame::NoFrame);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(560, 40, 40, 25));
        label_2->setFrameShape(QFrame::NoFrame);
        link2 = new QSpinBox(centralwidget);
        link2->setObjectName(QString::fromUtf8("link2"));
        link2->setGeometry(QRect(600, 40, 170, 25));
        link2->setMinimum(1);
        link2->setMaximum(30);
        generate = new QPushButton(centralwidget);
        generate->setObjectName(QString::fromUtf8("generate"));
        generate->setGeometry(QRect(560, 100, 211, 24));
        reset = new QPushButton(centralwidget);
        reset->setObjectName(QString::fromUtf8("reset"));
        reset->setGeometry(QRect(560, 220, 211, 24));
        copyright = new QLabel(centralwidget);
        copyright->setObjectName(QString::fromUtf8("copyright"));
        copyright->setEnabled(false);
        copyright->setGeometry(QRect(10, 597, 761, 16));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(560, 70, 40, 25));
        label_3->setFrameShape(QFrame::NoFrame);
        link3 = new QSpinBox(centralwidget);
        link3->setObjectName(QString::fromUtf8("link3"));
        link3->setGeometry(QRect(600, 70, 170, 25));
        link3->setMinimum(1);
        link3->setMaximum(30);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(560, 190, 45, 25));
        label_4->setFrameShape(QFrame::NoFrame);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(560, 160, 45, 25));
        label_5->setFrameShape(QFrame::NoFrame);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(560, 130, 45, 25));
        label_6->setFrameShape(QFrame::NoFrame);
        joint1 = new QSlider(centralwidget);
        joint1->setObjectName(QString::fromUtf8("joint1"));
        joint1->setGeometry(QRect(612, 130, 90, 25));
        joint1->setMaximum(360);
        joint1->setOrientation(Qt::Horizontal);
        joint1_val = new QLabel(centralwidget);
        joint1_val->setObjectName(QString::fromUtf8("joint1_val"));
        joint1_val->setGeometry(QRect(710, 130, 60, 25));
        joint1_val->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0)"));
        joint2_val = new QLabel(centralwidget);
        joint2_val->setObjectName(QString::fromUtf8("joint2_val"));
        joint2_val->setGeometry(QRect(710, 160, 60, 25));
        joint2_val->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0)"));
        joint2 = new QSlider(centralwidget);
        joint2->setObjectName(QString::fromUtf8("joint2"));
        joint2->setGeometry(QRect(612, 160, 90, 25));
        joint2->setMaximum(360);
        joint2->setOrientation(Qt::Horizontal);
        joint3_val = new QLabel(centralwidget);
        joint3_val->setObjectName(QString::fromUtf8("joint3_val"));
        joint3_val->setGeometry(QRect(710, 190, 60, 25));
        joint3_val->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0)"));
        joint3 = new QSlider(centralwidget);
        joint3->setObjectName(QString::fromUtf8("joint3"));
        joint3->setGeometry(QRect(612, 190, 90, 25));
        joint3->setMaximum(360);
        joint3->setOrientation(Qt::Horizontal);
        armGraphics = new QGraphicsView(centralwidget);
        armGraphics->setObjectName(QString::fromUtf8("armGraphics"));
        armGraphics->setGeometry(QRect(10, 10, 541, 581));
        mainwindow->setCentralWidget(centralwidget);

        retranslateUi(mainwindow);

        QMetaObject::connectSlotsByName(mainwindow);
    } // setupUi

    void retranslateUi(QMainWindow *mainwindow)
    {
        mainwindow->setWindowTitle(QApplication::translate("mainwindow", "3DOF_ROBOT_ARM", nullptr));
        label->setText(QApplication::translate("mainwindow", "link1", nullptr));
        label_2->setText(QApplication::translate("mainwindow", "link2", nullptr));
        generate->setText(QApplication::translate("mainwindow", "Generate Arm", nullptr));
        reset->setText(QApplication::translate("mainwindow", "Reset", nullptr));
        copyright->setText(QApplication::translate("mainwindow", " \302\251github.com.mjlee111/qt_example/3DOF_robot_arm", nullptr));
        label_3->setText(QApplication::translate("mainwindow", "link3", nullptr));
        label_4->setText(QApplication::translate("mainwindow", "joint3", nullptr));
        label_5->setText(QApplication::translate("mainwindow", "joint2", nullptr));
        label_6->setText(QApplication::translate("mainwindow", "joint1", nullptr));
        joint1_val->setText(QString());
        joint2_val->setText(QString());
        joint3_val->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class mainwindow: public Ui_mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
