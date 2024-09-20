#include "./ui_IMU.h"
#include "IMU.h"

IMU::IMU(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::IMU)
  , serialPort(new QSerialPort(this))
  , colorResetTimer(new QTimer(this))
  , colorResetTimer2(new QTimer(this))
  , cubeWidget(new CubeWidget(this))
{
  ui->setupUi(this);
  QIcon icon(":/image/images/icon.jpg");
  setWindowIcon(icon);

  ui->imu_graphics->setLayout(new QVBoxLayout());
  ui->imu_graphics->layout()->addWidget(cubeWidget);

  ui->device->addItems(getAvailableDevices());
  setupBaudRateComboBox(ui->rate);
  colorResetTimer->setSingleShot(true);
  colorResetTimer2->setSingleShot(true);

  connect(colorResetTimer, &QTimer::timeout, this, &IMU::resetRxLabelColor);
  connect(colorResetTimer2, &QTimer::timeout, this, &IMU::resetTxLabelColor);
}

IMU::~IMU()
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

bool IMU::openDevice(const QString& portName, const int baudRate)
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

void IMU::readDevice()
{
  if (serialPort->canReadLine())
  {
    ui->rx->setStyleSheet("QLabel {background-color: rgb(0, 254, 0)}");
    QByteArray data = serialPort->readAll();
    QString text(data);
    appendToTextEdit(ui->read, text);
    imuData imuIndex;
    imuIndex = parseIMUData(text);

    ui->roll->setText(QString::number(imuIndex.roll, 'f', 4));
    ui->pitch->setText(QString::number(imuIndex.pitch, 'f', 4));
    ui->yaw->setText(QString::number(imuIndex.yaw, 'f', 4));

    cubeWidget->rotateCube(toDEG(imuIndex.roll), toDEG(imuIndex.pitch), toDEG(imuIndex.yaw));

    Q_EMIT dataReceived();
    colorResetTimer->start(50);
  }
}

imuData IMU::parseIMUData(const QString& data)
{
  imuData imuIndex;

  if (!data.startsWith("*"))
  {
    return imuIndex;
  }

  QString headerTrimmed = data.mid(1);
  QStringList dataList = headerTrimmed.split(',');

  if (dataList.size() >= 3)
  {
    imuIndex.roll = dataList[0].toDouble();
    imuIndex.pitch = dataList[1].toDouble();
    imuIndex.yaw = dataList[2].toDouble();
  }
  return imuIndex;
}

void IMU::resetRxLabelColor()
{
  ui->rx->setStyleSheet("QLabel {background-color: rgb(72, 72, 72)}");
}

void IMU::resetTxLabelColor()
{
  ui->tx->setStyleSheet("QLabel {background-color: rgb(72, 72, 72)}");
}

void IMU::writeToDevice(const QString& data)
{
  if (serialPort->isOpen())
  {
    serialPort->write(data.toUtf8());
  }
}

void IMU::writeToDevice(const QByteArray& byte_data)
{
  serialPort->write(byte_data);
}

void IMU::closeDevice()
{
  if (serialPort->isOpen())
  {
    serialPort->close();
  }
}

QStringList IMU::getAvailableDevices()
{
  QStringList devicesList;

  const auto availablePorts = QSerialPortInfo::availablePorts();
  for (const QSerialPortInfo& portInfo : availablePorts)
  {
    devicesList.append(portInfo.portName());
  }

  return devicesList;
}

void IMU::setupBaudRateComboBox(QComboBox* comboBox)
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

void IMU::on_device_btn_clicked()
{
  if (isOpen)
  {
    disconnect(serialPort, &QSerialPort::readyRead, this, &IMU::readDevice);

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

      connect(serialPort, &QSerialPort::readyRead, this, &IMU::readDevice);
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

void IMU::on_clear_btn_clicked()
{
  ui->read->clear();
}

void IMU::on_device_currentIndexChanged(int index)
{
  device_name = ui->device->currentText();
}

void IMU::on_rate_currentIndexChanged(int index)
{
  baud_rate = ui->rate->itemData(index).toInt();
}

// void IMU::on_auto_scroll_checkStateChanged(const Qt::CheckState &arg1) {
//   autoScroll = arg1;
// }

// void IMU::on_clear_write_checkStateChanged(const Qt::CheckState &arg1) {
//   clearWrite = arg1;
// }

void IMU::on_write_btn_clicked()
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

void IMU::appendToLabel(QLabel* label, const QString& textToAppend)
{
  QString currentText = label->text();
  QString newText = currentText + textToAppend;
  label->setText(newText);
}

void IMU::appendToTextEdit(QTextEdit* textEdit, const QString& textToAppend)
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

void IMU::on_auto_scroll_stateChanged(int arg1)
{
  autoScroll = arg1;
}

void IMU::on_clear_write_stateChanged(int arg1)
{
  clearWrite = arg1;
}

EulerAngles IMU::quaternionToEulerAngles(const Quaternion& q)
{
  EulerAngles angles;

  float sinr_cosp = 2.0 * (q.w * q.x + q.y * q.z);
  float cosr_cosp = 1.0 - 2.0 * (q.x * q.x + q.y * q.y);
  angles.roll = std::atan2(sinr_cosp, cosr_cosp);

  float sinp = 2.0 * (q.w * q.y - q.z * q.x);
  if (std::abs(sinp) >= 1.0)
    angles.pitch = std::copysign(M_PI / 2.0, sinp);
  else
    angles.pitch = std::asin(sinp);

  float siny_cosp = 2.0 * (q.w * q.z + q.x * q.y);
  float cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z);
  angles.yaw = std::atan2(siny_cosp, cosy_cosp);

  return angles;
}

double IMU::toRAD(double deg)
{
  return deg * M_PI / 180;
}

double IMU::toDEG(double rad)
{
  return rad * 180 / M_PI;
}
