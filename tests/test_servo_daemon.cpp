/**
 * @file test_servo_daemon.cpp
 * @brief ServoDaemon CLI 유닛 테스트
 * @details 하드웨어 연결 시 실제 테스트, 미연결 시 Mock 폴백
 * @date 2026-02-09
 */

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

// Windows Serial Port Detection
#ifdef _WIN32
#include <windows.h>
#endif

// =============================================================================
// Simple Test Framework (No external dependencies)
// =============================================================================
namespace test {

struct TestResult {
  std::string name;
  bool passed;
  std::string message;
};

std::vector<TestResult> results;
int totalTests = 0;
int passedTests = 0;
int skippedTests = 0;

void runTest(const std::string &name, std::function<void()> testFn) {
  totalTests++;
  try {
    testFn();
    passedTests++;
    results.push_back({name, true, "OK"});
    std::cout << "  [PASS] " << name << std::endl;
  } catch (const std::exception &e) {
    std::string msg = e.what();
    if (msg.find("SKIP") != std::string::npos) {
      skippedTests++;
      results.push_back({name, true, "SKIPPED"});
      std::cout << "  [SKIP] " << name << " - " << msg << std::endl;
    } else {
      results.push_back({name, false, msg});
      std::cout << "  [FAIL] " << name << " - " << msg << std::endl;
    }
  }
}

void EXPECT_TRUE(bool condition, const std::string &msg = "") {
  if (!condition) {
    throw std::runtime_error(msg.empty() ? "Expected true, got false" : msg);
  }
}

void EXPECT_FALSE(bool condition, const std::string &msg = "") {
  if (condition) {
    throw std::runtime_error(msg.empty() ? "Expected false, got true" : msg);
  }
}

void EXPECT_EQ(int expected, int actual, const std::string &msg = "") {
  if (expected != actual) {
    throw std::runtime_error((msg.empty() ? "" : msg + ": ") + "Expected " +
                             std::to_string(expected) + ", got " +
                             std::to_string(actual));
  }
}

void EXPECT_EQ(size_t expected, size_t actual, const std::string &msg = "") {
  if (expected != actual) {
    throw std::runtime_error((msg.empty() ? "" : msg + ": ") + "Expected " +
                             std::to_string(expected) + ", got " +
                             std::to_string(actual));
  }
}

void EXPECT_GT(int value, int threshold, const std::string &msg = "") {
  if (!(value > threshold)) {
    throw std::runtime_error((msg.empty() ? "" : msg + ": ") + "Expected > " +
                             std::to_string(threshold) + ", got " +
                             std::to_string(value));
  }
}

void SKIP(const std::string &reason) {
  throw std::runtime_error("SKIP: " + reason);
}

void printSummary() {
  std::cout << "\n========================================" << std::endl;
  std::cout << "  Test Summary: " << passedTests << "/" << totalTests
            << " passed";
  if (skippedTests > 0) {
    std::cout << " (" << skippedTests << " skipped)";
  }
  std::cout << std::endl;
  std::cout << "========================================" << std::endl;

  int failedCount = totalTests - passedTests;
  if (failedCount == 0) {
    std::cout << "  All tests PASSED!" << std::endl;
  } else {
    std::cout << "  FAILED tests:" << std::endl;
    for (const auto &r : results) {
      if (!r.passed) {
        std::cout << "    - " << r.name << ": " << r.message << std::endl;
      }
    }
  }
}

} // namespace test

// =============================================================================
// Hardware Detection
// =============================================================================
namespace hw {

std::vector<std::string> getAvailablePorts() {
  std::vector<std::string> ports;

#ifdef _WIN32
  // Enumerate COM ports on Windows
  for (int i = 1; i <= 256; ++i) {
    std::string portName = "COM" + std::to_string(i);
    std::string path = "\\\\.\\" + portName;

    HANDLE hPort = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0,
                               nullptr, OPEN_EXISTING, 0, nullptr);

    if (hPort != INVALID_HANDLE_VALUE) {
      CloseHandle(hPort);
      ports.push_back(portName);
    }
  }
#endif

  return ports;
}

bool isHardwareConnected() {
  auto ports = getAvailablePorts();
  // 간단한 휴리스틱: COM 포트가 있으면 하드웨어가 연결되었다고 가정
  return !ports.empty();
}

// Simple SerialPort class for hardware tests
class SerialPort {
public:
  bool open(const std::string &portName, int baudRate) {
#ifdef _WIN32
    std::string path = "\\\\.\\" + portName;
    hPort_ = CreateFileA(path.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr,
                         OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);

    if (hPort_ == INVALID_HANDLE_VALUE) {
      return false;
    }

    // Configure port
    DCB dcb = {0};
    dcb.DCBlength = sizeof(DCB);
    GetCommState(hPort_, &dcb);
    dcb.BaudRate = baudRate;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity = NOPARITY;
    SetCommState(hPort_, &dcb);

    // Set timeouts
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 100;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 100;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hPort_, &timeouts);

    isOpen_ = true;
    return true;
#else
    return false;
#endif
  }

  void close() {
#ifdef _WIN32
    if (hPort_ != INVALID_HANDLE_VALUE) {
      CloseHandle(hPort_);
      hPort_ = INVALID_HANDLE_VALUE;
    }
#endif
    isOpen_ = false;
  }

  bool isOpen() const { return isOpen_; }

  int write(const uint8_t *data, int len) {
#ifdef _WIN32
    DWORD written = 0;
    if (WriteFile(hPort_, data, len, &written, nullptr)) {
      return static_cast<int>(written);
    }
#endif
    return -1;
  }

  int read(uint8_t *data, int maxLen) {
#ifdef _WIN32
    DWORD bytesRead = 0;
    if (ReadFile(hPort_, data, maxLen, &bytesRead, nullptr)) {
      return static_cast<int>(bytesRead);
    }
#endif
    return -1;
  }

  ~SerialPort() { close(); }

private:
  bool isOpen_ = false;
#ifdef _WIN32
  HANDLE hPort_ = INVALID_HANDLE_VALUE;
#endif
};

// =============================================================================
// SMS_STS Register Addresses
// =============================================================================
constexpr uint8_t SMS_STS_MODEL_L = 3;
constexpr uint8_t SMS_STS_MODEL_H = 4;
constexpr uint8_t SMS_STS_ID = 5;
constexpr uint8_t SMS_STS_BAUD_RATE = 6;
constexpr uint8_t SMS_STS_PRESENT_POSITION_L = 56;
constexpr uint8_t SMS_STS_PRESENT_POSITION_H = 57;
constexpr uint8_t SMS_STS_PRESENT_SPEED_L = 58;
constexpr uint8_t SMS_STS_PRESENT_SPEED_H = 59;
constexpr uint8_t SMS_STS_PRESENT_LOAD_L = 60;
constexpr uint8_t SMS_STS_PRESENT_LOAD_H = 61;
constexpr uint8_t SMS_STS_PRESENT_VOLTAGE = 62;
constexpr uint8_t SMS_STS_PRESENT_TEMPERATURE = 63;
constexpr uint8_t SMS_STS_MOVING = 66;
constexpr uint8_t SMS_STS_PRESENT_CURRENT_L = 69;
constexpr uint8_t SMS_STS_PRESENT_CURRENT_H = 70;

// Servo Status Structure
struct ServoStatus {
  int modelNumber = -1;
  int position = -1;
  int speed = -1;
  int load = -1;
  int voltage = -1;     // 0.1V unit
  int temperature = -1; // Celsius
  int current = -1;     // mA
  int moving = -1;

  bool isValid() const {
    return position >= 0 && position <= 4095 && voltage >= 0 &&
           voltage <= 255 && temperature >= 0 && temperature <= 100;
  }

  void print() const {
    std::cout << "      Position: " << position << " (0-4095)" << std::endl;
    std::cout << "      Speed: " << speed << std::endl;
    std::cout << "      Load: " << load << " (0-1000)" << std::endl;
    std::cout << "      Voltage: " << (voltage / 10.0) << " V" << std::endl;
    std::cout << "      Temperature: " << temperature << " C" << std::endl;
    std::cout << "      Current: " << current << " mA" << std::endl;
    std::cout << "      Moving: " << moving << std::endl;
  }
};

// =============================================================================
// SCServo Protocol Implementation
// =============================================================================

// SCServo Ping Protocol Implementation
int pingServo(SerialPort &port, uint8_t id) {
  // Feetech SCServo Ping Packet: FF FF ID LEN INST CHECKSUM
  // INST_PING = 0x01
  uint8_t packet[6];
  packet[0] = 0xFF;
  packet[1] = 0xFF;
  packet[2] = id;
  packet[3] = 2;    // Length (INST + CHECKSUM)
  packet[4] = 0x01; // INST_PING

  // Checksum: ~(ID + LEN + INST) & 0xFF
  uint8_t checksum = ~(packet[2] + packet[3] + packet[4]) & 0xFF;
  packet[5] = checksum;

  // Send
  if (port.write(packet, 6) != 6) {
    return -1;
  }

  // Wait for response
  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // Read response: FF FF ID LEN ERR CHECKSUM (최소 6바이트)
  uint8_t response[32];
  int bytesRead = port.read(response, sizeof(response));

  // Check for valid response
  if (bytesRead >= 6 && response[0] == 0xFF && response[1] == 0xFF) {
    return response[2]; // Return responding ID
  }

  return -1;
}

// Read single byte from servo memory
int readByte(SerialPort &port, uint8_t id, uint8_t address) {
  // INST_READ = 0x02
  // Packet: FF FF ID LEN INST ADDR READ_LEN CHECKSUM
  uint8_t packet[8];
  packet[0] = 0xFF;
  packet[1] = 0xFF;
  packet[2] = id;
  packet[3] = 4;    // Length (INST + ADDR + READ_LEN + CHECKSUM)
  packet[4] = 0x02; // INST_READ
  packet[5] = address;
  packet[6] = 1; // Read 1 byte

  uint8_t checksum =
      ~(packet[2] + packet[3] + packet[4] + packet[5] + packet[6]) & 0xFF;
  packet[7] = checksum;

  if (port.write(packet, 8) != 8) {
    return -1;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // Response: FF FF ID LEN ERR DATA CHECKSUM
  uint8_t response[32];
  int bytesRead = port.read(response, sizeof(response));

  if (bytesRead >= 7 && response[0] == 0xFF && response[1] == 0xFF) {
    // response[5] is the data byte
    return response[5];
  }

  return -1;
}

// Read word (2 bytes) from servo memory
int readWord(SerialPort &port, uint8_t id, uint8_t address) {
  // Packet: FF FF ID LEN INST ADDR READ_LEN CHECKSUM
  uint8_t packet[8];
  packet[0] = 0xFF;
  packet[1] = 0xFF;
  packet[2] = id;
  packet[3] = 4;    // Length
  packet[4] = 0x02; // INST_READ
  packet[5] = address;
  packet[6] = 2; // Read 2 bytes

  uint8_t checksum =
      ~(packet[2] + packet[3] + packet[4] + packet[5] + packet[6]) & 0xFF;
  packet[7] = checksum;

  if (port.write(packet, 8) != 8) {
    return -1;
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(10));

  // Response: FF FF ID LEN ERR DATA_L DATA_H CHECKSUM
  uint8_t response[32];
  int bytesRead = port.read(response, sizeof(response));

  if (bytesRead >= 8 && response[0] == 0xFF && response[1] == 0xFF) {
    // Little-endian: low byte first
    int16_t value = response[5] | (response[6] << 8);
    return value;
  }

  return -1;
}

// Read all servo status values
ServoStatus readServoStatus(SerialPort &port, uint8_t id) {
  ServoStatus status;

  status.modelNumber = readWord(port, id, SMS_STS_MODEL_L);
  status.position = readWord(port, id, SMS_STS_PRESENT_POSITION_L);
  status.speed = readWord(port, id, SMS_STS_PRESENT_SPEED_L);
  status.load = readWord(port, id, SMS_STS_PRESENT_LOAD_L);
  status.voltage = readByte(port, id, SMS_STS_PRESENT_VOLTAGE);
  status.temperature = readByte(port, id, SMS_STS_PRESENT_TEMPERATURE);
  status.current = readWord(port, id, SMS_STS_PRESENT_CURRENT_L);
  status.moving = readByte(port, id, SMS_STS_MOVING);

  return status;
}

} // namespace hw

// =============================================================================
// Test Helpers (Simulated servo logic without hardware)
// =============================================================================

// Endianness conversion (from scserial.h)
void host_2_scs(uint8_t *data_l, uint8_t *data_h, uint16_t data) {
  *data_l = static_cast<uint8_t>(data & 0xFF);
  *data_h = static_cast<uint8_t>((data >> 8) & 0xFF);
}

uint16_t scs_2_host(uint8_t data_l, uint8_t data_h) {
  return static_cast<uint16_t>(data_l) | (static_cast<uint16_t>(data_h) << 8);
}

// Command type validation
bool isValidCommandType(const std::string &type) {
  static const std::vector<std::string> validTypes = {
      "connect", "disconnect", "shutdown", "ping",          "write_pos",
      "scan",    "read_state", "write",    "enable_torque", "sync_write_pos"};
  return std::find(validTypes.begin(), validTypes.end(), type) !=
         validTypes.end();
}

// Servo state validation
struct ServoState {
  int id;
  int position;
  int speed;
  int load;
  int voltage;
  int temperature;
  int current;

  bool isValid() const {
    return id >= 1 && id <= 253 && position >= -32768 && position <= 32767 &&
           voltage >= 0 && voltage <= 255 && temperature >= 0 &&
           temperature <= 100;
  }
};

// Simulated scan
std::vector<int32_t> simulateScan(int startId, int endId,
                                  const std::vector<int> &existingServos) {
  std::vector<int32_t> foundIds;
  for (int id = startId; id <= endId; ++id) {
    if (std::find(existingServos.begin(), existingServos.end(), id) !=
        existingServos.end()) {
      foundIds.push_back(id);
    }
  }
  return foundIds;
}

// =============================================================================
// Mock Tests (Always run)
// =============================================================================
void runMockTests() {
  std::cout << "[Endianness Tests]" << std::endl;

  test::runTest("Host2Scs_ConvertsCorrectly", []() {
    uint8_t low, high;
    host_2_scs(&low, &high, 0x1234);
    test::EXPECT_EQ(0x34, static_cast<int>(low), "Low byte");
    test::EXPECT_EQ(0x12, static_cast<int>(high), "High byte");
  });

  test::runTest("Scs2Host_ConvertsCorrectly", []() {
    uint16_t result = scs_2_host(0x34, 0x12);
    test::EXPECT_EQ(0x1234, static_cast<int>(result));
  });

  test::runTest("Endianness_RoundTrip", []() {
    uint16_t original = 2048;
    uint8_t low, high;
    host_2_scs(&low, &high, original);
    uint16_t reconstructed = scs_2_host(low, high);
    test::EXPECT_EQ(static_cast<int>(original),
                    static_cast<int>(reconstructed));
  });

  std::cout << "\n[Command Type Tests]" << std::endl;

  test::runTest("CommandType_Connect_Valid",
                []() { test::EXPECT_TRUE(isValidCommandType("connect")); });

  test::runTest("CommandType_Disconnect_Valid",
                []() { test::EXPECT_TRUE(isValidCommandType("disconnect")); });

  test::runTest("CommandType_Scan_Valid",
                []() { test::EXPECT_TRUE(isValidCommandType("scan")); });

  test::runTest("CommandType_ReadState_Valid",
                []() { test::EXPECT_TRUE(isValidCommandType("read_state")); });

  test::runTest("CommandType_WritePos_Valid",
                []() { test::EXPECT_TRUE(isValidCommandType("write_pos")); });

  test::runTest("CommandType_SyncWritePos_Valid", []() {
    test::EXPECT_TRUE(isValidCommandType("sync_write_pos"));
  });

  test::runTest("CommandType_EnableTorque_Valid", []() {
    test::EXPECT_TRUE(isValidCommandType("enable_torque"));
  });

  test::runTest("CommandType_Invalid_Rejected", []() {
    test::EXPECT_FALSE(isValidCommandType("invalid"));
    test::EXPECT_FALSE(isValidCommandType(""));
    test::EXPECT_FALSE(isValidCommandType("CONNECT"));
  });

  std::cout << "\n[Servo State Tests]" << std::endl;

  test::runTest("ServoState_ValidState", []() {
    ServoState state = {1, 2048, 100, 500, 120, 45, 300};
    test::EXPECT_TRUE(state.isValid());
  });

  test::runTest("ServoState_InvalidId_Zero", []() {
    ServoState state = {0, 2048, 100, 500, 120, 45, 300};
    test::EXPECT_FALSE(state.isValid());
  });

  test::runTest("ServoState_InvalidId_TooHigh", []() {
    ServoState state = {254, 2048, 100, 500, 120, 45, 300};
    test::EXPECT_FALSE(state.isValid());
  });

  test::runTest("ServoState_BoundaryId_1", []() {
    ServoState state = {1, 2048, 100, 500, 120, 45, 300};
    test::EXPECT_TRUE(state.isValid());
  });

  test::runTest("ServoState_BoundaryId_253", []() {
    ServoState state = {253, 2048, 100, 500, 120, 45, 300};
    test::EXPECT_TRUE(state.isValid());
  });

  std::cout << "\n[Scan Tests (Mock)]" << std::endl;

  test::runTest("Scan_FindsExistingServos", []() {
    std::vector<int> existing = {1, 2, 3};
    auto found = simulateScan(1, 253, existing);
    test::EXPECT_EQ(size_t(3), found.size());
  });

  test::runTest("Scan_ReturnsEmptyWhenNoServos", []() {
    std::vector<int> existing = {};
    auto found = simulateScan(1, 253, existing);
    test::EXPECT_EQ(size_t(0), found.size());
  });

  test::runTest("Scan_PartialRange", []() {
    std::vector<int> existing = {1, 50, 100, 200};
    auto found = simulateScan(40, 110, existing);
    test::EXPECT_EQ(size_t(2), found.size());
  });

  std::cout << "\n[Position Value Tests]" << std::endl;

  test::runTest("Position_CenterValue", []() {
    int pos = 2048;
    test::EXPECT_TRUE(pos >= 0 && pos <= 4095);
  });

  test::runTest("Position_NegativeEncoding", []() {
    int16_t pos = -1000;
    if (pos < 0) {
      pos = static_cast<int16_t>(-pos);
      pos |= (1 << 15);
    }
    test::EXPECT_TRUE((pos & (1 << 15)) != 0, "Bit 15 should be set");
  });
}

// =============================================================================
// Hardware Tests (Run only when hardware is connected)
// =============================================================================
void runHardwareTests(const std::string &portName, int baudRate) {
  std::cout << "\n[Hardware Tests - " << portName << " @ " << baudRate << "]"
            << std::endl;

  hw::SerialPort port;

  test::runTest("HW_OpenPort", [&]() {
    bool opened = port.open(portName, baudRate);
    test::EXPECT_TRUE(opened, "Failed to open " + portName);
  });

  if (!port.isOpen()) {
    std::cout << "  Skipping remaining hardware tests (port not open)"
              << std::endl;
    return;
  }

  test::runTest("HW_PingServo_ID1", [&]() {
    int result = hw::pingServo(port, 1);
    if (result == -1) {
      test::SKIP("No servo at ID 1");
    }
    test::EXPECT_EQ(1, result, "Servo ID mismatch");
  });

  test::runTest("HW_PingServo_ID2", [&]() {
    int result = hw::pingServo(port, 2);
    if (result == -1) {
      test::SKIP("No servo at ID 2");
    }
    test::EXPECT_EQ(2, result, "Servo ID mismatch");
  });

  test::runTest("HW_ScanServos", [&]() {
    std::vector<int> found;
    std::cout << "    Scanning IDs 1-10..." << std::endl;

    for (int id = 1; id <= 10; ++id) {
      int result = hw::pingServo(port, static_cast<uint8_t>(id));
      if (result > 0) {
        found.push_back(result);
        std::cout << "      Found servo ID: " << result << std::endl;
      }
    }

    if (found.empty()) {
      test::SKIP("No servos found in range 1-10");
    }

    test::EXPECT_GT(static_cast<int>(found.size()), 0,
                    "Should find at least one servo");
  });

  // === Comprehensive Status Reading Tests ===
  std::cout << "\n[Hardware Status Tests]" << std::endl;

  // Store first found servo ID for subsequent tests
  int testServoId = 1;

  test::runTest("HW_ReadPosition", [&]() {
    int pos = hw::readWord(port, testServoId, hw::SMS_STS_PRESENT_POSITION_L);
    if (pos == -1) {
      test::SKIP("Failed to read position");
    }
    std::cout << "    Position: " << pos << std::endl;
    test::EXPECT_TRUE(pos >= 0 && pos <= 4095,
                      "Position out of range (0-4095): " + std::to_string(pos));
  });

  test::runTest("HW_ReadSpeed", [&]() {
    int speed = hw::readWord(port, testServoId, hw::SMS_STS_PRESENT_SPEED_L);
    if (speed == -1) {
      test::SKIP("Failed to read speed");
    }
    std::cout << "    Speed: " << speed << std::endl;
    // Speed can be negative (direction), so check absolute value
    int absSpeed = (speed < 0) ? -speed : speed;
    test::EXPECT_TRUE(absSpeed >= 0 && absSpeed <= 32767,
                      "Speed out of range: " + std::to_string(speed));
  });

  test::runTest("HW_ReadLoad", [&]() {
    int load = hw::readWord(port, testServoId, hw::SMS_STS_PRESENT_LOAD_L);
    if (load == -1) {
      test::SKIP("Failed to read load");
    }
    std::cout << "    Load: " << load << " (0-1000)" << std::endl;
    // Load can have sign bit for direction
    int absLoad = load & 0x3FF; // Lower 10 bits
    test::EXPECT_TRUE(absLoad >= 0 && absLoad <= 1000,
                      "Load out of range (0-1000): " + std::to_string(absLoad));
  });

  test::runTest("HW_ReadVoltage", [&]() {
    int voltage = hw::readByte(port, testServoId, hw::SMS_STS_PRESENT_VOLTAGE);
    if (voltage == -1) {
      test::SKIP("Failed to read voltage");
    }
    double voltageV = voltage / 10.0;
    std::cout << "    Voltage: " << voltageV << " V" << std::endl;
    // Typical range: 5V - 15V (50 - 150 in 0.1V units)
    test::EXPECT_TRUE(voltage >= 40 && voltage <= 180,
                      "Voltage out of expected range (4-18V): " +
                          std::to_string(voltageV) + "V");
  });

  test::runTest("HW_ReadTemperature", [&]() {
    int temp = hw::readByte(port, testServoId, hw::SMS_STS_PRESENT_TEMPERATURE);
    if (temp == -1) {
      test::SKIP("Failed to read temperature");
    }
    std::cout << "    Temperature: " << temp << " C" << std::endl;
    // Operating temperature: typically 0-85°C
    test::EXPECT_TRUE(
        temp >= 0 && temp <= 100,
        "Temperature out of range (0-100C): " + std::to_string(temp) + "C");
  });

  test::runTest("HW_ReadCurrent", [&]() {
    int current =
        hw::readWord(port, testServoId, hw::SMS_STS_PRESENT_CURRENT_L);
    if (current == -1) {
      test::SKIP("Failed to read current");
    }
    std::cout << "    Current: " << current << " mA" << std::endl;
    // Current range: typically 0-2000mA
    int absCurrent = (current < 0) ? -current : current;
    test::EXPECT_TRUE(absCurrent >= 0 && absCurrent <= 5000,
                      "Current out of range: " + std::to_string(current) +
                          "mA");
  });

  test::runTest("HW_ReadMoving", [&]() {
    int moving = hw::readByte(port, testServoId, hw::SMS_STS_MOVING);
    if (moving == -1) {
      test::SKIP("Failed to read moving status");
    }
    std::cout << "    Moving: " << (moving ? "Yes" : "No") << std::endl;
    test::EXPECT_TRUE(moving == 0 || moving == 1,
                      "Moving flag should be 0 or 1: " +
                          std::to_string(moving));
  });

  test::runTest("HW_ReadModelNumber", [&]() {
    int model = hw::readWord(port, testServoId, hw::SMS_STS_MODEL_L);
    if (model == -1) {
      test::SKIP("Failed to read model number");
    }
    std::cout << "    Model Number: " << model << std::endl;
    test::EXPECT_TRUE(model > 0, "Model number should be positive");
  });

  // === Full Status Validation ===
  test::runTest("HW_FullStatusValid", [&]() {
    hw::ServoStatus status = hw::readServoStatus(port, testServoId);

    std::cout << "    --- Full Servo Status ---" << std::endl;
    status.print();

    test::EXPECT_TRUE(status.isValid(), "Servo status validation failed");
  });

  port.close();

  test::runTest("HW_ClosePort", [&]() {
    test::EXPECT_FALSE(port.isOpen(), "Port should be closed");
  });
}

// =============================================================================
// Main Entry Point
// =============================================================================
int main(int argc, char **argv) {
  std::cout << "\n";
  std::cout << "========================================" << std::endl;
  std::cout << "  ServoDaemon Unit Tests (CLI)" << std::endl;
  std::cout << "========================================" << std::endl;

  // Parse command line arguments
  std::string portOverride = "";
  int baudRate = 1000000;
  bool forceHardware = false;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-h" || arg == "--help") {
      std::cout << "\nUsage: " << argv[0] << " [options]" << std::endl;
      std::cout << "Options:" << std::endl;
      std::cout << "  -p, --port <PORT>   Specify COM port (e.g., COM3)"
                << std::endl;
      std::cout << "  -b, --baud <RATE>   Specify baud rate (default: 1000000)"
                << std::endl;
      std::cout << "  --hw                Force hardware tests" << std::endl;
      std::cout << "  -h, --help          Show this help" << std::endl;
      return 0;
    } else if ((arg == "-p" || arg == "--port") && i + 1 < argc) {
      portOverride = argv[++i];
    } else if ((arg == "-b" || arg == "--baud") && i + 1 < argc) {
      baudRate = std::stoi(argv[++i]);
    } else if (arg == "--hw") {
      forceHardware = true;
    }
  }

  // Detect hardware
  std::cout << "\n[Hardware Detection]" << std::endl;
  auto ports = hw::getAvailablePorts();

  if (ports.empty()) {
    std::cout << "  No COM ports found - running Mock tests only" << std::endl;
  } else {
    std::cout << "  Available COM ports: ";
    for (const auto &p : ports) {
      std::cout << p << " ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;

  // Run Mock tests (always)
  runMockTests();

  // Run Hardware tests (if hardware connected or forced)
  std::string testPort =
      portOverride.empty() ? (ports.empty() ? "" : ports[0]) : portOverride;

  if (!testPort.empty() && (forceHardware || hw::isHardwareConnected())) {
    runHardwareTests(testPort, baudRate);
  } else if (forceHardware && testPort.empty()) {
    std::cout << "\n[Hardware Tests]" << std::endl;
    std::cout << "  SKIPPED: No COM port available" << std::endl;
  }

  // Print Summary
  test::printSummary();

  // Return exit code
  int failed = test::totalTests - test::passedTests;
  return (failed == 0) ? 0 : 1;
}
