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
  } else if (type == "scan") {
    handleScan();
  } else if (type == "read_state") {
    handleReadState(cmd.servo_id());
  } else if (type == "write") {
    handleWrite(cmd.servo_id(), cmd.address(), cmd.value(), cmd.size());
  } else if (type == "enable_torque") {
    handleEnableTorque(cmd.servo_id(), cmd.value() != 0);
  } else if (type == "sync_write_pos") {
    std::vector<int32_t> ids(cmd.target_ids().begin(), cmd.target_ids().end());
    handleSyncWritePos(ids, cmd.value(), cmd.speed(), cmd.acc());
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

// =============================================================================
// Phase 2: Servo Control Handlers
// =============================================================================

void ServoDaemon::handleScan() {
  std::cout << "[Daemon] Starting servo scan (ID 1-253)..." << std::endl;

  if (!serial_ || !serial_->isOpen()) {
    std::cerr << "[Daemon] Error: Port not open for scan." << std::endl;
    sendFeedback("error", "Port not open", true);
    return;
  }

  found_servo_ids_.clear();

  for (int id = 1; id <= 253; ++id) {
    int ret = sc_serial_->ping(static_cast<uint8_t>(id));
    if (ret > 0) {
      std::cout << "[Daemon] Found Servo ID: " << ret << std::endl;
      found_servo_ids_.push_back(ret);
    }
  }

  std::cout << "[Daemon] Scan complete. Found " << found_servo_ids_.size()
            << " servos." << std::endl;
  sendScanResult(found_servo_ids_);
}

void ServoDaemon::handleReadState(int servoId) {
  if (!serial_ || !serial_->isOpen()) {
    sendFeedback("error", "Port not open", true);
    return;
  }

  // SMS_STS 프로토콜 기준으로 상태 읽기
  int pos = sms_sts_->read_position(servoId);
  int speed = sms_sts_->read_speed(servoId);
  int load = sms_sts_->read_load(servoId);
  int voltage = sms_sts_->read_voltage(servoId);
  int temp = sms_sts_->read_temperature(servoId);
  int current = sms_sts_->read_current(servoId);
  int moving = sms_sts_->read_move(servoId);

  sendServoState(servoId, pos, speed, load, voltage, temp, current, moving > 0);
}

void ServoDaemon::handleWrite(int servoId, int address, int value, int size) {
  if (!serial_ || !serial_->isOpen()) {
    sendFeedback("error", "Port not open", true);
    return;
  }

  std::cout << "[Daemon] Write (ID: " << servoId << ", Addr: " << address
            << ", Val: " << value << ", Size: " << size << ")" << std::endl;

  int ret = 0;
  if (size == 2) {
    ret = sc_serial_->write_word(static_cast<uint8_t>(servoId),
                                 static_cast<uint8_t>(address),
                                 static_cast<uint16_t>(value));
  } else {
    ret = sc_serial_->write_byte(static_cast<uint8_t>(servoId),
                                 static_cast<uint8_t>(address),
                                 static_cast<uint8_t>(value));
  }

  if (ret == -1) {
    sendFeedback("error", "Write failed", true);
  } else {
    sendFeedback("ack", "Write OK");
  }
}

void ServoDaemon::handleEnableTorque(int servoId, bool enable) {
  if (!serial_ || !serial_->isOpen()) {
    sendFeedback("error", "Port not open", true);
    return;
  }

  std::cout << "[Daemon] Torque " << (enable ? "Enable" : "Disable")
            << " (ID: " << servoId << ")" << std::endl;

  int ret =
      sms_sts_->enable_torque(static_cast<uint8_t>(servoId), enable ? 1 : 0);
  if (ret == -1) {
    sendFeedback("error", "Torque control failed", true);
  } else {
    sendFeedback("ack", enable ? "Torque enabled" : "Torque disabled");
  }
}

void ServoDaemon::handleSyncWritePos(const std::vector<int32_t> &ids,
                                     int position, int speed, int acc) {
  if (!serial_ || !serial_->isOpen()) {
    sendFeedback("error", "Port not open", true);
    return;
  }

  if (ids.empty()) {
    sendFeedback("error", "No target IDs specified", true);
    return;
  }

  std::cout << "[Daemon] SyncWritePos to " << ids.size() << " servos"
            << " (Pos: " << position << ", Spd: " << speed << ", Acc: " << acc
            << ")" << std::endl;

  // 각 서보에 동일한 위치 명령 전송
  std::vector<uint8_t> idArr;
  std::vector<int16_t> posArr;
  std::vector<uint16_t> spdArr;
  std::vector<uint8_t> accArr;

  for (int32_t id : ids) {
    idArr.push_back(static_cast<uint8_t>(id));
    posArr.push_back(static_cast<int16_t>(position));
    spdArr.push_back(static_cast<uint16_t>(speed));
    accArr.push_back(static_cast<uint8_t>(acc));
  }

  sms_sts_->sync_write_pos_ex(idArr.data(), static_cast<uint8_t>(idArr.size()),
                              posArr.data(), spdArr.data(), accArr.data());
  sendFeedback("ack", "SyncWrite OK");
}

void ServoDaemon::sendScanResult(const std::vector<int32_t> &foundIds) {
  if (!feedback_writer_)
    return;

  scservo::ServoFeedback fb;
  fb.feedback_type("scan_result");
  fb.connected(serial_ && serial_->isOpen());

  // found_ids에 결과 복사
  fb.found_ids(foundIds);

  std::string msg = "Found " + std::to_string(foundIds.size()) + " servos";
  fb.message(msg);

  feedback_writer_->write(fb);
}

void ServoDaemon::sendServoState(int id, int pos, int speed, int load,
                                 int voltage, int temp, int current,
                                 bool moving) {
  if (!feedback_writer_)
    return;

  scservo::ServoFeedback fb;
  fb.feedback_type("servo_state");
  fb.connected(serial_ && serial_->isOpen());

  // ServoState 구조체 채우기
  scservo::ServoState state;
  state.id(id);
  state.position(pos);
  state.speed(speed);
  state.load(load);
  state.voltage(voltage);
  state.temperature(temp);
  state.current(current);
  state.moving(moving);

  fb.state(state);
  fb.message("State update for ID " + std::to_string(id));

  feedback_writer_->write(fb);
}

void ServoDaemon::broadcastServoStates() {
  if (!serial_ || !serial_->isOpen() || found_servo_ids_.empty())
    return;

  // 모든 발견된 서보의 상태를 브로드캐스트
  for (int32_t id : found_servo_ids_) {
    int pos = sms_sts_->read_position(id);
    int speed = sms_sts_->read_speed(id);
    int load = sms_sts_->read_load(id);
    int voltage = sms_sts_->read_voltage(id);
    int temp = sms_sts_->read_temperature(id);
    int current = sms_sts_->read_current(id);
    int moving = sms_sts_->read_move(id);

    sendServoState(id, pos, speed, load, voltage, temp, current, moving > 0);
  }
}
