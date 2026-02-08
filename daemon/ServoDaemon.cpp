/**
 * @file ServoDaemon.cpp
 * @brief ServoDaemon 클래스 구현부
 * @details DDS Listener 구현 및 각 명령어 처리 로직을 포함합니다.
 * @date 2026-02-08
 */

#include "ServoDaemon.hpp"
#include "SerialPort.hpp"
#include "scservo.hpp"
#include "servo/scscl.h"
#include "servo/scserial.h"
#include "servo/sms_sts.h"


#include <chrono>
#include <iostream>
#include <thread>


// --- DDS Listener Class ---
class DaemonListener
    : public dds::sub::NoOpDataReaderListener<scservo::ServoCommand> {
public:
  explicit DaemonListener(ServoDaemon *daemon) : daemon_(daemon) {}

  void on_data_available(
      dds::sub::DataReader<scservo::ServoCommand> &reader) override {
    try {
      auto samples = reader.take();
      for (const auto &sample : samples) {
        if (sample.info().valid()) {
          // ServoDaemon의 public 메서드 호출
          daemon_->processCommand(sample.data());
        }
      }
    } catch (const std::exception &ex) {
      std::cerr << "[Daemon] Listener Error: " << ex.what() << std::endl;
    }
  }

private:
  ServoDaemon *daemon_;
};

// --- ServoDaemon Implementation ---

ServoDaemon::ServoDaemon() {
  // 하드웨어 인터페이스 초기화
  serial_ = std::make_unique<SerialPort>();
  sc_serial_ = std::make_unique<feetech_servo::SCSerial>(serial_.get());
  sms_sts_ = std::make_unique<feetech_servo::SMS_STS>(sc_serial_.get());
  scscl_ = std::make_unique<feetech_servo::SCSCL>(sc_serial_.get());
}

ServoDaemon::~ServoDaemon() { stop(); }

bool ServoDaemon::start() {
  std::cout << "[Daemon] Starting services..." << std::endl;

  if (!initDDS()) {
    std::cerr << "[Daemon] Failed to initialize DDS." << std::endl;
    return false;
  }

  running_ = true;
  std::cout << "[Daemon] Started successfully." << std::endl;
  return true;
}

void ServoDaemon::stop() {
  running_ = false;
  if (serial_ && serial_->isOpen()) {
    serial_->close();
  }
}

void ServoDaemon::run() {
  int count = 0;
  std::cout << "[Daemon] Heartbeat loop started (1s interval)." << std::endl;

  // 메인 스레드 블로킹 루프 (1초 주기 Heartbeat)
  while (running_) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string msg = "Heartbeat #" + std::to_string(++count);

    // 콘솔에 로그 출력 (디버깅용) - CMD와 구분하기 위해 prefix 사용
    std::cout << "[Daemon HB] " << msg << std::endl;

    sendFeedback("ping", msg);
  }
}

bool ServoDaemon::initDDS() {
  try {
    // DomainParticipant 생성
    participant_ = std::make_unique<dds::domain::DomainParticipant>(0);

    // Topics
    dds::topic::Topic<scservo::ServoCommand> cmd_topic(*participant_,
                                                       "ServoCommand");
    dds::topic::Topic<scservo::ServoFeedback> fb_topic(*participant_,
                                                       "ServoFeedback");

    // Publisher & Writer
    dds::pub::Publisher pub(*participant_);
    feedback_writer_ =
        std::make_unique<dds::pub::DataWriter<scservo::ServoFeedback>>(
            pub, fb_topic);

    // Subscriber & Listener
    dds::sub::Subscriber sub(*participant_);
    auto listener = std::make_shared<DaemonListener>(this);

    // Reader 생성
    command_reader_ =
        std::make_unique<dds::sub::DataReader<scservo::ServoCommand>>(
            sub, cmd_topic, dds::sub::qos::DataReaderQos(), listener,
            dds::core::status::StatusMask::data_available());

    return true;
  } catch (const std::exception &ex) {
    std::cerr << "[Daemon] DDS Init Exception: " << ex.what() << std::endl;
    return false;
  }
}

void ServoDaemon::processCommand(const scservo::ServoCommand &cmd) {
  std::string type = cmd.command_type();

  // 중요: 모든 커맨드 수신 로그 출력 (사용자 확인용)
  std::cout << "\n[Daemon >>> CMD] Type: " << type << std::endl;

  if (type == "connect") {
    handleConnect(cmd.port_name(), cmd.baud_rate());
  } else if (type == "disconnect") {
    handleDisconnect();
  } else if (type == "shutdown") {
    std::cout << "[Daemon] Shutdown command received. Exiting..." << std::endl;
    running_ = false;
  } else if (type == "ping") {
    handlePing(cmd.value());
  } else if (type == "write_pos") {
    handleWritePos(cmd.servo_id(), cmd.value(), cmd.speed(), cmd.acc());
  } else {
    std::cout << "[Daemon] Unknown Command: " << type << std::endl;
  }
}

void ServoDaemon::handleConnect(const std::string &port, int baudRate) {
  std::cout << "[Daemon] Connecting to " << port << " @ " << baudRate << "..."
            << std::endl;

  if (serial_->isOpen())
    serial_->close();

  serial_->setPortName(port);
  serial_->setBaudRate(baudRate);

  if (serial_->open(SerialPort::ReadWrite)) {
    std::cout << "[Daemon] Success: Connected to " << port << std::endl;
    sendStatus(true, port);
  } else {
    std::cerr << "[Daemon] Error: Connection failed: " << port << std::endl;
    sendFeedback("error", "Failed to open port: " + port, true);
    sendStatus(false);
  }
}

void ServoDaemon::handleDisconnect() {
  std::cout << "[Daemon] Disconnecting..." << std::endl;
  if (serial_->isOpen()) {
    serial_->close();
    std::cout << "[Daemon] Disconnected." << std::endl;
  }
  sendStatus(false);
}

void ServoDaemon::handlePing(int value) {
  std::cout << "[Daemon] Ping received (Val: " << value << "). Sending Pong."
            << std::endl;
  sendFeedback("pong", "Pong from Daemon (Val: " + std::to_string(value) + ")");
}

void ServoDaemon::handleWritePos(int id, int position, int speed, int acc) {
  std::cout << "[Daemon] WritePos (ID: " << id << ", Pos: " << position
            << ", Spd: " << speed << ", Acc: " << acc << ")" << std::endl;

  if (!serial_->isOpen()) {
    std::cerr << "[Daemon] Error: Port not open." << std::endl;
    sendFeedback("error", "Port not open", true);
    return;
  }

  int ret = sms_sts_->write_pos_ex(
      static_cast<uint8_t>(id), static_cast<int16_t>(position),
      static_cast<uint16_t>(speed), static_cast<uint8_t>(acc));

  if (ret == -1) {
    std::cerr << "[Daemon] Error: Write failed (Hardware)." << std::endl;
    sendFeedback("error", "Write failed", true);
  } else {
    // std::cout << "[Daemon] Write success." << std::endl;
  }
}

void ServoDaemon::sendFeedback(const std::string &type, const std::string &msg,
                               bool isError) {
  if (!feedback_writer_)
    return;

  try {
    scservo::ServoFeedback fb;
    fb.feedback_type(type);
    fb.message(msg);
    fb.is_error(isError);
    fb.connected(serial_ && serial_->isOpen());
    fb.timestamp(std::chrono::duration_cast<std::chrono::milliseconds>(
                     std::chrono::system_clock::now().time_since_epoch())
                     .count());

    feedback_writer_->write(fb);
  } catch (...) {
  }
}

void ServoDaemon::sendStatus(bool connected, const std::string &currentPort) {
  if (!feedback_writer_)
    return;

  scservo::ServoFeedback fb;
  fb.feedback_type("status");
  fb.connected(connected);
  fb.current_port(currentPort);
  fb.message(connected ? "Connected" : "Disconnected");

  feedback_writer_->write(fb);
}
