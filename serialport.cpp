#include "serialport.h"
#include "serialportch34x.h"
#include "serialportcp210x.h"
#include "serialportdummy.h"
#include "serialportqt.h"

SerialPort::SerialPort(QObject *parent) : QObject(parent) {
  currentBaudRate = QSerialPort::UnknownBaud;
  currentDataBits = QSerialPort::UnknownDataBits;
  currentParity = QSerialPort::UnknownParity;
  currentStopBits = QSerialPort::UnknownStopBits;
  currentFlowControl = QSerialPort::UnknownFlowControl;
}

QList<SerialPort *> SerialPort::getAvailablePorts(QObject *parent) {
  QList<SerialPort *> result;
  result.append(SerialPortCP210X::availablePorts(parent));
  result.append(SerialPortCH34X::availablePorts(parent));
  result.append(SerialPortQt::availablePorts(parent));
  result.append(SerialPortDummy::availablePorts(parent));
  return result;
}