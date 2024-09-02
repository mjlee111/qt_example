#ifndef SERIAL_H
#define SERIAL_H

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

QT_BEGIN_NAMESPACE
namespace Ui
{
class Serial;
}
QT_END_NAMESPACE

class Serial : public QMainWindow
{
  Q_OBJECT

public:
  Serial(QWidget* parent = nullptr);
  ~Serial();

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
  Ui::Serial* ui;
  QSerialPort* serialPort;
  QTimer* colorResetTimer;
  QTimer* colorResetTimer2;

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
};
#endif  // SERIAL_H
