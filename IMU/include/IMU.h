#ifndef IMU_H
#define IMU_H

#include <QComboBox>
#include <QMainWindow>
#include <QMessageBox>
#include <QScrollBar>
#include <QSerialPort>
#include <QTextEdit>
#include <QThread>
#include <QTimer>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>
#include <math.h>

#include "CubeWidget.h"

struct Quaternion
{
  float w;
  float x;
  float y;
  float z;
};

struct EulerAngles
{
  float roll;
  float pitch;
  float yaw;
};

struct imuData
{
  double roll;
  double pitch;
  double yaw;
};

QT_BEGIN_NAMESPACE
namespace Ui
{
class IMU;
}
QT_END_NAMESPACE

class IMU : public QMainWindow
{
  Q_OBJECT

public:
  IMU(QWidget* parent = nullptr);
  ~IMU();

signals:
  void dataReceived();

public slots:
  void readDevice();
  void writeToDevice(const QString& data);
  void writeToDevice(const QByteArray& byte_data);

private slots:
  void on_device_currentIndexChanged(int index);
  void on_rate_currentIndexChanged(int index);
  void on_device_btn_clicked();
  void on_clear_btn_clicked();
  // void on_auto_scroll_checkStateChanged(const Qt::CheckState &arg1);
  // void on_clear_write_checkStateChanged(const Qt::CheckState &arg1);
  void on_auto_scroll_stateChanged(int arg1);
  void on_clear_write_stateChanged(int arg1);

  void on_write_btn_clicked();

  void resetRxLabelColor();
  void resetTxLabelColor();

private:
  Ui::IMU* ui;
  QSerialPort* serialPort;
  QTimer* colorResetTimer;
  QTimer* colorResetTimer2;
  CubeWidget* cubeWidget;

  bool isOpen = false;
  bool autoScroll = false;
  bool clearWrite = false;

  QString device_name;
  int baud_rate = -1;

  void setupBaudRateComboBox(QComboBox* comboBox);
  QStringList getAvailableDevices();
  bool openDevice(const QString& portName, const int baudRate);
  void closeDevice();

  QSerialPort::BaudRate convertIntToBaudRate(int baudRate);
  void appendToLabel(QLabel* label, const QString& textToAppend);
  void appendToTextEdit(QTextEdit* textEdit, const QString& textToAppend);

  imuData parseIMUData(const QString& data);

  EulerAngles quaternionToEulerAngles(const Quaternion& q);
  double toRAD(double deg);
  double toDEG(double rad);
};
#endif  // IMU_H
