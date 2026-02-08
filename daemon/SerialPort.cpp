#include "SerialPort.hpp"
#include <iostream>
#include <string>
#include <vector>


#pragma comment(lib, "advapi32.lib")

SerialPort::SerialPort()
    : hSerial_(INVALID_HANDLE_VALUE), baudRate_(1000000), parity_(NoParity),
      dataBits_(8), stopBits_(OneStop), flowControl_(NoFlowControl),
      isOpen_(false) {}

SerialPort::~SerialPort() { close(); }

void SerialPort::setPortName(const std::string &name) { portName_ = name; }

void SerialPort::setBaudRate(int baudRate) { baudRate_ = baudRate; }

void SerialPort::setParity(Parity parity) { parity_ = parity; }

void SerialPort::setDataBits(int dataBits) { dataBits_ = dataBits; }

void SerialPort::setStopBits(StopBits stopBits) { stopBits_ = stopBits; }

void SerialPort::setFlowControl(FlowControl flowControl) {
  flowControl_ = flowControl;
}

bool SerialPort::open(OpenMode mode) {
  if (isOpen_)
    close();

  std::string portPath = "\\\\.\\" + portName_;
  hSerial_ = CreateFileA(portPath.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
                         NULL, OPEN_EXISTING, 0, NULL);

  if (hSerial_ == INVALID_HANDLE_VALUE) {
    return false;
  }

  DCB dcbSerialParams = {0};
  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

  if (!GetCommState(hSerial_, &dcbSerialParams)) {
    CloseHandle(hSerial_);
    return false;
  }

  dcbSerialParams.BaudRate = baudRate_;
  dcbSerialParams.ByteSize = dataBits_;
  dcbSerialParams.StopBits =
      (stopBits_ == OneStop)
          ? ONESTOPBIT
          : (stopBits_ == TwoStop ? TWOSTOPBITS : ONE5STOPBITS);
  dcbSerialParams.Parity =
      (parity_ == NoParity) ? NOPARITY
                            : (parity_ == OddParity ? ODDPARITY : EVENPARITY);

  // Flow Control
  if (flowControl_ == NoFlowControl) {
    dcbSerialParams.fOutxCtsFlow = FALSE;
    dcbSerialParams.fRtsControl = RTS_CONTROL_DISABLE;
  }

  if (!SetCommState(hSerial_, &dcbSerialParams)) {
    CloseHandle(hSerial_);
    return false;
  }

  // Timeouts
  COMMTIMEOUTS timeouts = {0};
  timeouts.ReadIntervalTimeout = 3; // 매우 짧게 대기 (polling)
  timeouts.ReadTotalTimeoutConstant = 1;
  timeouts.ReadTotalTimeoutMultiplier = 1;
  timeouts.WriteTotalTimeoutConstant = 50;
  timeouts.WriteTotalTimeoutMultiplier = 10;

  if (!SetCommTimeouts(hSerial_, &timeouts)) {
    CloseHandle(hSerial_);
    return false;
  }

  isOpen_ = true;
  return true;
}

void SerialPort::close() {
  if (isOpen_ && hSerial_ != INVALID_HANDLE_VALUE) {
    CloseHandle(hSerial_);
    hSerial_ = INVALID_HANDLE_VALUE;
    isOpen_ = false;
  }
}

bool SerialPort::isOpen() const { return isOpen_; }

int SerialPort::write(const char *data, int len) {
  if (!isOpen_)
    return -1;

  DWORD bytesWritten;
  if (!WriteFile(hSerial_, data, len, &bytesWritten, NULL)) {
    return -1;
  }
  return bytesWritten;
}

int SerialPort::read(char *data, int len) {
  if (!isOpen_)
    return -1;

  DWORD bytesRead;
  if (!ReadFile(hSerial_, data, len, &bytesRead, NULL)) {
    return -1;
  }
  return bytesRead;
}

bool SerialPort::waitForReadyRead(int msecs) {
  if (!isOpen_)
    return false;
  // Windows API에서는 비동기 I/O나 WaitCommEvent를 써야 하지만,
  // 여기서는 간단히 Sleep으로 대체하거나, bytesAvailable을 체크하는 방식으로
  // 구현 scserial에서는 주로 bytesAvailable() 체크 후 read()를 호출함.

  // 단순 지연
  Sleep(msecs > 0 ? msecs : 1);
  return true;
}

int SerialPort::bytesAvailable() {
  if (!isOpen_)
    return 0;

  DWORD errors;
  COMSTAT status;
  ClearCommError(hSerial_, &errors, &status);
  return status.cbInQue;
}

std::vector<SerialPort::PortInfo> SerialPort::availablePorts() {
  std::vector<PortInfo> ports;
  char path[5000]; // 버퍼 충분히

  // QueryDosDevice를 사용하여 모든 디바이스 목록 조회 후 COM 포트 필터링
  if (QueryDosDeviceA(NULL, path, 5000)) {
    char *p = path;
    while (*p) {
      std::string deviceName(p);
      if (deviceName.find("COM") == 0) {
        PortInfo info;
        info.portName = deviceName;
        info.description =
            deviceName; // 자세한 설명은 레지스트리를 읽어야 하므로 생략
        ports.push_back(info);
      }
      p += strlen(p) + 1;
    }
  }
  return ports;
}
