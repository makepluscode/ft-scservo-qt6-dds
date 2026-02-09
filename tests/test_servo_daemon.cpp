/**
 * @file test_servo_daemon.cpp
 * @brief ServoDaemon CLI 유닛 테스트
 * @details 외부 의존성 없이 순수 C++17로 구현한 CLI 기반 테스트
 * @date 2026-02-09
 */

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <vector>


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

#define TEST(name)                                                             \
  void test_##name();                                                          \
  struct TestRegistrar_##name {                                                \
    TestRegistrar_##name() { runTest(#name, test_##name); }                    \
  } testRegistrar_##name;                                                      \
  void test_##name()

void runTest(const std::string &name, std::function<void()> testFn) {
  totalTests++;
  try {
    testFn();
    passedTests++;
    results.push_back({name, true, "OK"});
    std::cout << "  [PASS] " << name << std::endl;
  } catch (const std::exception &e) {
    results.push_back({name, false, e.what()});
    std::cout << "  [FAIL] " << name << " - " << e.what() << std::endl;
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

void printSummary() {
  std::cout << "\n========================================" << std::endl;
  std::cout << "  Test Summary: " << passedTests << "/" << totalTests
            << " passed" << std::endl;
  std::cout << "========================================" << std::endl;

  if (passedTests == totalTests) {
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
// Test Helpers (Simulated servo logic without hardware)
// =============================================================================

// Endianness conversion (from scserial.h)
void host_2_scs(uint8_t *data_l, uint8_t *data_h, uint16_t data) {
  // SMS_STS uses little-endian
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
// Tests
// =============================================================================

void runAllTests() {
  std::cout << "========================================" << std::endl;
  std::cout << "  ServoDaemon Unit Tests (CLI)" << std::endl;
  std::cout << "========================================" << std::endl;
  std::cout << std::endl;

  // --- Endianness Conversion Tests ---
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

  // --- Command Type Tests ---
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
    test::EXPECT_FALSE(isValidCommandType("CONNECT")); // Case sensitive
  });

  // --- Servo State Validation Tests ---
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

  // --- Scan Tests ---
  std::cout << "\n[Scan Tests]" << std::endl;

  test::runTest("Scan_FindsExistingServos", []() {
    std::vector<int> existing = {1, 2, 3};
    auto found = simulateScan(1, 253, existing);
    test::EXPECT_EQ(size_t(3), found.size());
    test::EXPECT_EQ(1, found[0]);
    test::EXPECT_EQ(2, found[1]);
    test::EXPECT_EQ(3, found[2]);
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
    test::EXPECT_EQ(50, found[0]);
    test::EXPECT_EQ(100, found[1]);
  });

  // --- Position Value Tests ---
  std::cout << "\n[Position Value Tests]" << std::endl;

  test::runTest("Position_CenterValue", []() {
    int pos = 2048; // Center position
    test::EXPECT_TRUE(pos >= 0 && pos <= 4095);
  });

  test::runTest("Position_NegativeEncoding", []() {
    int16_t pos = -1000;
    // Simulate SMS_STS negative encoding
    if (pos < 0) {
      pos = static_cast<int16_t>(-pos);
      pos |= (1 << 15);
    }
    test::EXPECT_TRUE((pos & (1 << 15)) != 0, "Bit 15 should be set");
  });

  // --- Print Summary ---
  test::printSummary();
}

// =============================================================================
// Main Entry Point
// =============================================================================
int main(int argc, char **argv) {
  std::cout << "\n";

  // Parse command line arguments
  bool verbose = false;
  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    if (arg == "-v" || arg == "--verbose") {
      verbose = true;
    } else if (arg == "-h" || arg == "--help") {
      std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
      std::cout << "Options:" << std::endl;
      std::cout << "  -v, --verbose    Show detailed output" << std::endl;
      std::cout << "  -h, --help       Show this help" << std::endl;
      return 0;
    }
  }

  runAllTests();

  // Return exit code based on test results
  return (test::passedTests == test::totalTests) ? 0 : 1;
}
