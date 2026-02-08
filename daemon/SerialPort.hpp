#pragma once

/*
 * SerialPort - 간단한 Windows API 기반 시리얼 포트 클래스
 * Qt 의존성을 제거하고 scserial에서 사용하기 위해 QSerialPort 인터페이스를
 * 모방함.
 */

#include <cstdint>
#include <string>
#include <vector>
#include <windows.h>


class SerialPort {
public:
  struct PortInfo {
    std::string portName;
    std::string description;
  };

  enum Parity { NoParity = 0, OddParity = 1, EvenParity = 2 };

  enum StopBits { OneStop = 0, OneAndHalfStop = 1, TwoStop = 2 };

  enum FlowControl { NoFlowControl, HardwareControl, SoftwareControl };

  enum OpenMode { ReadWrite };

  SerialPort();
  ~SerialPort();

  void setPortName(const std::string &name);
  void setBaudRate(int baudRate);
  void setParity(Parity parity);
  void setDataBits(int dataBits);
  void setStopBits(StopBits stopBits);
  void setFlowControl(FlowControl flowControl);

  bool open(OpenMode mode);
  void close();
  bool isOpen() const;

  int write(const char *data, int len);
  int read(char *data, int len);

  // 타임아웃
  bool waitForReadyRead(int msecs);
  int bytesAvailable();

  static std::vector<PortInfo> availablePorts();

private:
  HANDLE hSerial_;
  std::string portName_;
  int baudRate_;
  Parity parity_;
  int dataBits_;
  StopBits stopBits_;
  FlowControl flowControl_;
  bool isOpen_;
};
