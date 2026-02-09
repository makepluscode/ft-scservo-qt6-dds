/**
 * @file ServoDaemon.hpp
 * @brief FT SCServo 제어 및 DDS 통신을 담당하는 메인 클래스 헤더
 * @details Daemon의 주요 로직(통신, 제어, 피드백)을 캡슐화합니다.
 * @date 2026-02-08
 */

#pragma once

#include <atomic>
#include <dds/dds.hpp>
#include <memory>
#include <string>
#include <vector>

// Forward declarations to reduce compilation dependencies
class SerialPort;
namespace feetech_servo {
class SCSerial;
class SMS_STS;
class SCSCL;
} // namespace feetech_servo
namespace scservo {
class ServoCommand;
class ServoFeedback;
} // namespace scservo

/**
 * @class ServoDaemon
 * @brief 서보 모터 제어와 DDS 통신을 중개하는 Daemon 클래스
 */
class ServoDaemon {
public:
  ServoDaemon();
  ~ServoDaemon();

  /**
   * @brief Daemon 초기화 및 시작
   * @return 성공 시 true, 실패 시 false
   */
  bool start();

  /**
   * @brief Daemon 종료 및 리소스 해제
   */
  void stop();

  /**
   * @brief 실행 루프 (블로킹 동작)
   * @note 현재는 무한 대기하지만, 추후 주기적 작업이 추가될 수 있음.
   */
  void run();

  /**
   * @brief DDS Command 수신 처리 메서드
   * @details Listener 클래스에서 호출하여 수신된 명령을 처리합니다.
   * @param cmd 수신된 명령어 데이터
   */
  void processCommand(const scservo::ServoCommand &cmd);

private:
  // --- Internal Initialization Methods ---
  bool initDDS();

  // --- Command Handler Implementations ---
  void handleConnect(const std::string &port, int baudRate);
  void handleDisconnect();
  void handlePing(int value);
  void handleWritePos(int id, int position, int speed, int acc);
  void handleScan();
  void handleReadState(int servoId);
  void handleWrite(int servoId, int address, int value, int size);
  void handleEnableTorque(int servoId, bool enable);
  void handleSyncWritePos(const std::vector<int32_t> &ids, int position,
                          int speed, int acc);

  // --- Feedback Helper Methods ---
  void sendFeedback(const std::string &type, const std::string &msg,
                    bool isError = false);
  void sendStatus(bool connected, const std::string &currentPort = "");
  void sendScanResult(const std::vector<int32_t> &foundIds);
  void sendServoState(int id, int pos, int speed, int load, int voltage,
                      int temp, int current);

  // --- Periodic state broadcast ---
  void broadcastServoStates();

private:
  std::atomic<bool> running_{false};

  // --- Servo State Management ---
  std::vector<int32_t> found_servo_ids_;
  int selected_servo_id_{-1};

  // --- Hardware Interfaces (PIMPL idiom via unique_ptr) ---
  std::unique_ptr<SerialPort> serial_;
  std::unique_ptr<feetech_servo::SCSerial> sc_serial_;
  std::unique_ptr<feetech_servo::SMS_STS> sms_sts_;
  std::unique_ptr<feetech_servo::SCSCL> scscl_;

  // --- DDS Interfaces ---
  std::unique_ptr<dds::domain::DomainParticipant> participant_;
  std::unique_ptr<dds::pub::DataWriter<scservo::ServoFeedback>>
      feedback_writer_;
  // CommandReader는 멤버변수로 유지하여 수명 관리 (Listener와 연관)
  std::unique_ptr<dds::sub::DataReader<scservo::ServoCommand>> command_reader_;
};
