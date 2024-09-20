#include "./ui_serial.h"
#include "serial.h"

Serial::Serial(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::Serial)
  , serialPort(new QSerialPort(this))
  , colorResetTimer(new QTimer(this))
  , colorResetTimer2(new QTimer(this))
{
  ui->setupUi(this);
  QIcon icon(":/image/images/serial.png");
  setWindowIcon(icon);
  ui->device->addItems(getAvailableDevices());
  setupBaudRateComboBox(ui->rate);
  colorResetTimer->setSingleShot(true);
  colorResetTimer2->setSingleShot(true);

  connect(colorResetTimer, &QTimer::timeout, this, &Serial::resetRxLabelColor);
  connect(colorResetTimer2, &QTimer::timeout, this, &Serial::resetTxLabelColor);
}

Serial::~Serial()
{
  if (serialPort->isOpen())
  {
    serialPort->close();
  }
  delete serialPort;
  delete colorResetTimer;
  delete colorResetTimer2;
  delete ui;
}

bool Serial::openDevice(const QString& portName, const int baudRate)
{
  if (serialPort->isOpen())
  {
    serialPort->close();
  }

  serialPort->setPortName(portName);
  serialPort->setBaudRate(baudRate);
  serialPort->setDataBits(QSerialPort::Data8);
  serialPort->setParity(QSerialPort::NoParity);
  serialPort->setStopBits(QSerialPort::OneStop);
  serialPort->setFlowControl(QSerialPort::NoFlowControl);

  if (serialPort->open(QIODevice::ReadWrite))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void Serial::readDevice()
{
  if (serialPort->canReadLine())
  {
    ui->rx->setStyleSheet("QLabel {background-color: rgb(0, 254, 0)}");
    QByteArray data = serialPort->readAll();
    QString text(data);
    appendToTextEdit(ui->read, text);
    Q_EMIT dataReceived();
    colorResetTimer->start(50);
  }
}

void Serial::resetRxLabelColor()
{
  ui->rx->setStyleSheet("QLabel {background-color: rgb(72, 72, 72)}");
}

void Serial::resetTxLabelColor()
{
  ui->tx->setStyleSheet("QLabel {background-color: rgb(72, 72, 72)}");
}

void Serial::writeToDevice(const QString& data)
{
  if (serialPort->isOpen())
  {
    serialPort->write(data.toUtf8());
  }
}

void Serial::writeToDevice(const QByteArray& byte_data)
{
  serialPort->write(byte_data);
}

void Serial::closeDevice()
{
  if (serialPort->isOpen())
  {
    serialPort->close();
  }
}

QStringList Serial::getAvailableDevices()
{
  QStringList devicesList;

  const auto availablePorts = QSerialPortInfo::availablePorts();
  for (const QSerialPortInfo& portInfo : availablePorts)
  {
    devicesList.append(portInfo.portName());
  }

  return devicesList;
}

void Serial::setupBaudRateComboBox(QComboBox* comboBox)
{
  comboBox->addItem("1200", 1200);
  comboBox->addItem("2400", 2400);
  comboBox->addItem("4800", 4800);
  comboBox->addItem("9600", 9600);
  comboBox->addItem("19200", 19200);
  comboBox->addItem("38400", 38400);
  comboBox->addItem("57600", 57600);
  comboBox->addItem("115200", 115200);
  comboBox->addItem("230400", 230400);
  comboBox->addItem("460800", 460800);
  comboBox->addItem("921600", 921600);
  comboBox->addItem("1000000", 1000000);
  comboBox->addItem("2000000", 2000000);
  comboBox->addItem("4000000", 4000000);

  comboBox->setCurrentIndex(comboBox->findData("9600"));
}

void Serial::on_device_btn_clicked()
{
  if (isOpen)
  {
    disconnect(serialPort, &QSerialPort::readyRead, this, &Serial::readDevice);

    closeDevice();
    ui->device->setEnabled(true);
    ui->rate->setEnabled(true);
    ui->device_btn->setText("OPEN");
    isOpen = false;
    getAvailableDevices();
  }
  else if (!isOpen)
  {
    bool status = openDevice(device_name, baud_rate);
    if (status)
    {
      ui->device->setEnabled(false);
      ui->rate->setEnabled(false);
      ui->device_btn->setText("CLOSE");
      isOpen = true;

      connect(serialPort, &QSerialPort::readyRead, this, &Serial::readDevice);
    }
    else
    {
      QMessageBox::critical(nullptr, "Device Status", "Failed to open device: " + serialPort->errorString());
      ui->device->setEnabled(true);
      ui->rate->setEnabled(true);
      ui->device_btn->setText("OPEN");
      isOpen = false;
      getAvailableDevices();
    }
  }
}

void Serial::on_clear_btn_clicked()
{
  ui->read->clear();
}

void Serial::on_device_currentIndexChanged(int index)
{
  device_name = ui->device->currentText();
}

void Serial::on_rate_currentIndexChanged(int index)
{
  baud_rate = ui->rate->itemData(index).toInt();
}

// void Serial::on_auto_scroll_checkStateChanged(const Qt::CheckState &arg1) {
//   autoScroll = arg1;
// }

// void Serial::on_clear_write_checkStateChanged(const Qt::CheckState &arg1) {
//   clearWrite = arg1;
// }

void Serial::on_write_btn_clicked()
{
  if (serialPort->isOpen())
  {
    ui->tx->setStyleSheet("QLabel {background-color: rgb(0, 0, 254)}");
    writeToDevice(ui->write_data->toPlainText());
    if (clearWrite)
    {
      ui->write_data->clear();
    }
    colorResetTimer2->start(50);
  }
}

void Serial::appendToLabel(QLabel* label, const QString& textToAppend)
{
  QString currentText = label->text();
  QString newText = currentText + textToAppend;
  label->setText(newText);
}

void Serial::appendToTextEdit(QTextEdit* textEdit, const QString& textToAppend)
{
  textEdit->setText(textEdit->toPlainText() + textToAppend);
  if (autoScroll)
  {
    QTextCursor cursor = textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    textEdit->setTextCursor(cursor);
    textEdit->verticalScrollBar()->setValue(textEdit->verticalScrollBar()->maximum());
  }
}

void Serial::on_auto_scroll_stateChanged(int arg1)
{
  autoScroll = arg1;
}

void Serial::on_clear_write_stateChanged(int arg1)
{
  clearWrite = arg1;
}
