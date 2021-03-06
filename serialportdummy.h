#ifndef SERIALPORTDUMMY_H
#define SERIALPORTDUMMY_H

#include "serialport.h"

class SerialPortDummy : public SerialPort {
  Q_OBJECT

public:
  static QList<SerialPort *> availablePorts(QObject *parent = nullptr) {
    return QList<SerialPort *>{new SerialPortDummy(parent)};
  }
  QString portName() override { return "dummy"; }
  void setBaudRate(qint32) override {}
  qint32 getBaudRate() override { return 115200; }
  void setDataBits(QSerialPort::DataBits) override {}
  void setParity(QSerialPort::Parity) override {}
  QSerialPort::Parity getParity() override { return QSerialPort::NoParity; }
  void setStopBits(QSerialPort::StopBits) override {}
  void setFlowControl(QSerialPort::FlowControl) override {}
  bool open() override { return isOpening = true; }
  bool isOpen() override { return isOpening; }
  void close() override { isOpening = false; }

signals:
  void receivedData(QByteArray data);
  void breakChanged(bool set);

public slots:
  void sendData(const QByteArray &data) override { emit receivedData(data); }
  void triggerBreak(uint msecs) override { Q_UNUSED(msecs); };

private:
  SerialPortDummy(QObject *parent = nullptr) : SerialPort(parent) {
    isOpening = false;
  }
  ~SerialPortDummy() {}

  bool isOpening;
};

#endif