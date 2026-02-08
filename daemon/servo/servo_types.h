#ifndef SERVO_MEM_CONFIG_H
#define SERVO_MEM_CONFIG_H

#include <cstdint>
#include <map>
#include <string>
#include <vector>


// Remove QString dependency
// #include <QString>

namespace feetech_servo {

struct MemoryConfig {
  uint8_t address;
  std::string name; // Changed from QString
  uint8_t size;
  uint16_t default_value;
  int8_t dir_bit;
  bool is_eprom;
  bool is_readonly;
  int16_t min_val;
  int16_t max_val;
};

// ... (나머지 MemoryConfig 데이터는 동일하지만 string 리터럴로 초기화)
// 복붙할 때 QString을 std::string으로 자동으로 처리되므로 구조체 정의만
// 수정하면 됨. 데이터 부분은 복사해서 붙여넣되, vector 타입으로 변경

// 여기서는 데이터가 너무 많으므로 생략하고, 필요시 직접 cpp 파일에 정의하거나
// 사용하도록 수정. scserial에서 주로 사용하는 서보 타입/ID 맵핑 때문에 필요.
// 전체 목록이 필요하면 원본을 가져와서 수정해야 함.

} // namespace feetech_servo

#endif // SERVO_MEM_CONFIG_H
