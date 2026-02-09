#pragma once

#include "scserial.h"

namespace feetech_servo {

//-------EPROM(Read Only)--------
#define SMS_STS_FIRMWARE_MAJOR                                                 \
  0 // Firmware major version number. 펌웨어 메이저 버전 번호.
#define SMS_STS_FIRMWARE_MINOR                                                 \
  1 // Firmware minor version number. 펌웨어 마이너 버전 번호.
#define SMS_STS_SERVO_MAJOR                                                    \
  3 // Servo major version number. 서보 메이저 버전 번호.
#define SMS_STS_SERVO_MINOR                                                    \
  4 // Servo minor version number. 서보 마이너 버전 번호.

//-------EPROM(Read/Write)--------
#define SMS_STS_ID                                                             \
  5 // ID. 버스 상의 고유 식별 코드. 254(0xFE)는 브로드캐스트 ID.
#define SMS_STS_BAUD_RATE                                                      \
  6 // Baudrate. 0-7은 각각 1M, 500K, 250K, 128K, 115200, 76800, 57600, 38400을
    // 의미.
#define SMS_STS_RETURN_DELAY                                                   \
  7 // Return delay. 최소 단위 2us. 응답 지연 최대 설정 508us (254*2).
#define SMS_STS_RESPONSE_STATUS_LEVEL                                          \
  8 // Response status level. 0: Read/PING 외 응답 없음, 1: 모든 명령에 응답.
#define SMS_STS_MIN_ANGLE_LIMIT_L                                              \
  9 // Minimum angle. 동작 범위 최소값 제한. 멀티턴 모드 시 0. 최소값 -32766.
#define SMS_STS_MIN_ANGLE_LIMIT_H 10
#define SMS_STS_MAX_ANGLE_LIMIT_L                                              \
  11 // Maximum angle. 동작 범위 최대값 제한. 멀티턴 모드 시 0. 최대값 32767.
#define SMS_STS_MAX_ANGLE_LIMIT_H 12
#define SMS_STS_MAX_TEMPERATURE_LIMIT                                          \
  13 // Maximum temperature. 최대 작동 온도 제한. 단위 1°C. 예: 70 -> 70°C.
#define SMS_STS_MAX_INPUT_VOLTAGE                                              \
  14 // Maximum input voltage. 최대 입력 전압 제한. 단위 0.1V. 예: 80 -> 8.0V.
#define SMS_STS_MIN_INPUT_VOLTAGE                                              \
  15 // Minimum input voltage. 최소 입력 전압 제한. 단위 0.1V. 예: 40 -> 4.0V.
#define SMS_STS_MAX_TORQUE_L                                                   \
  16 // Maximum torque. 최대 출력 토크 제한. 1000은 100% 토크.
#define SMS_STS_MAX_TORQUE_H 17
#define SMS_STS_PHASE                                                          \
  18 // Phase. 특수 기능 바이트. 특별한 요구사항 없으면 수정 금지.
#define SMS_STS_UNLOADING_CONDITIONS                                           \
  19 // Unloading conditions. 비트 설정 시 해당 보호 활성화 (Voltage, Sensor,
     // Temp, Current, Angle, Overload).
#define SMS_STS_LED_ALARM_CONDITIONS                                           \
  20 // LED alarm conditions. 비트 설정 시 해당 LED 깜빡임 활성화.
#define SMS_STS_POS_P_COEFF                                                    \
  21 // Position loop P (Proportional) coefficient. 모터 제어 비례 계수.
#define SMS_STS_POS_D_COEFF                                                    \
  22 // Position loop D (Differential) coefficient. 모터 제어 미분 계수.
#define SMS_STS_POS_I_COEFF                                                    \
  23 // Position loop I (Integral) coefficient. 모터 제어 적분 계수.
#define SMS_STS_MIN_STARTING_FORCE_L                                           \
  24 // Minimum starting force. 최소 출력 시동 토크. 1000은 100%.
#define SMS_STS_MIN_STARTING_FORCE_H 25
#define SMS_STS_CW_DEAD                                                        \
  26 // Clockwise insensitive zone. 시계 방향 불감도 영역. 단위는 최소 분해능
     // 각도.
#define SMS_STS_CCW_DEAD                                                       \
  27 // Anti-clockwise insensitive zone. 반시계 방향 불감도 영역. 단위는 최소
     // 분해능 각도.
#define SMS_STS_PROTECTION_CURRENT_L                                           \
  28 // Protection current. 전류 제한. 500 * 6.5mA = 3250mA.
#define SMS_STS_PROTECTION_CURRENT_H 29
#define SMS_STS_ANGLE_RESOLUTION                                               \
  30 // Angle resolution. 센서 최소 분해능 각도 증폭 계수. 1-3. 멀티턴 제어 시
     // 0x12 BIT4=1 필요.
#define SMS_STS_OFS_L                                                          \
  31 // Position correction. 위치 보정. BIT11은 방향, 0-2047 스텝 범위.
#define SMS_STS_OFS_H 32
#define SMS_STS_MODE                                                           \
  33 // Operation mode. 0: 위치 서보, 1: 정속(0x2E), 2: PWM 오픈루프(0x2C), 3:
     // 스텝 서보(0x2A).
#define SMS_STS_PROTECTION_TORQUE                                              \
  34 // Protection torque. 과부하 보호 진입 후 출력 토크. 20 -> 20%.
#define SMS_STS_PROTECTION_TIME                                                \
  35 // Protection time. 과부하 지속 허용 시간. 200 -> 2초 (단위 10ms).
#define SMS_STS_OVERLOAD_TORQUE                                                \
  36 // Overload torque. 과부하 보호 시작 토크 임계값. 80 -> 80%.
#define SMS_STS_SPEED_P_COEFF                                                  \
  37 // Speed closed-loop proportional (P) coefficient. 정속 모드(모드 1) 속도
     // 루프 P 계수.
#define SMS_STS_OVERCURRENT_TIME                                               \
  38 // Overcurrent protection time. 과전류 보호 시간. 254 * 10ms = 2540ms.
#define SMS_STS_SPEED_I_COEFF                                                  \
  39 // Velocity closed-loop integral (I) coefficient. 정속 모드 속도 루프 I
     // 계수.

//-------SRAM(Read/Write)--------
#define SMS_STS_TORQUE_ENABLE                                                  \
  40 // Torque switch. 0: 출력 끄기, 1: 출력 켜기, 128: 현재 위치를 2048로 보정.
#define SMS_STS_ACC 41 // Acceleration. 가속도. 10 -> 1000 step/s^2.
#define SMS_STS_GOAL_POSITION_L                                                \
  42 // Target location. 목표 위치. 절대 위치 제어 모드.
#define SMS_STS_GOAL_POSITION_H 43
#define SMS_STS_GOAL_TIME_L                                                    \
  44 // Operation time. PWM 오픈루프 속도 제어 모드 운전 시간.
#define SMS_STS_GOAL_TIME_H 45
#define SMS_STS_GOAL_SPEED_L                                                   \
  46 // Operation speed. 운전 속도. step/s. 50 step/s = 0.732 RPM.
#define SMS_STS_GOAL_SPEED_H 47
#define SMS_STS_TORQUE_LIMIT_L                                                 \
  48 // Torque limit. 토크 제한. 초기값은 최대 토크(0x10).
#define SMS_STS_TORQUE_LIMIT_H 49
#define SMS_STS_LOCK                                                           \
  55 // Lock flag. 0: 쓰기 잠금 해제(EPROM 저장 가능), 1: 잠금(저장 불가).

//-------SRAM(Read Only)--------
#define SMS_STS_PRESENT_POSITION_L 56 // Current location. 현재 위치 피드백.
#define SMS_STS_PRESENT_POSITION_H 57
#define SMS_STS_PRESENT_SPEED_L 58 // Current speed. 현재 속도 피드백. step/s.
#define SMS_STS_PRESENT_SPEED_H 59
#define SMS_STS_PRESENT_LOAD_L                                                 \
  60 // Current load. 현재 부하. 전압 듀티 사이클. 0.1%.
#define SMS_STS_PRESENT_LOAD_H 61
#define SMS_STS_PRESENT_VOLTAGE 62     // Current voltage. 현재 전압. 0.1V.
#define SMS_STS_PRESENT_TEMPERATURE 63 // Current temperature. 현재 온도. °C.
#define SMS_STS_ASYNC_WRITE_FLAG                                               \
  64 // Asynchronous write flag. 비동기 쓰기 플래그.
#define SMS_STS_SERVO_STATUS                                                   \
  65 // Servo status. 에러 상태 비트 (Voltage, Sensor, Temp, Current, Angle,
     // Overload).
#define SMS_STS_MOVING 66            // Move flag. 1: 이동 중, 0: 정지.
#define SMS_STS_PRESENT_CURRENT_L 69 // Current current. 현재 전류. 6.5mA 단위.
#define SMS_STS_PRESENT_CURRENT_H 70

class SMS_STS {
public:
  SMS_STS(SCSerial *scserial_) : scserial_(scserial_) {}

  int write_pos_ex(uint8_t ID, int16_t Position, uint16_t Speed,
                   uint8_t ACC = 0) // 普通写单个舵机位置指令
  {
    if (Position < 0) {
      Position = static_cast<int16_t>(-Position);
      Position |= (1 << 15);
    }
    uint8_t bBuf[7];
    bBuf[0] = ACC;
    scserial_->host_2_scs(bBuf + 1, bBuf + 2, static_cast<uint16_t>(Position));
    scserial_->host_2_scs(bBuf + 3, bBuf + 4, 0);
    scserial_->host_2_scs(bBuf + 5, bBuf + 6, Speed);

    return scserial_->gen_write(ID, SMS_STS_ACC, bBuf, 7);
  }

  int reg_write_pos_ex(
      uint8_t ID, int16_t Position, uint16_t Speed,
      uint8_t ACC = 0) // 异步写单个舵机位置指令(RegWriteAction生效)
  {
    if (Position < 0) {
      Position = static_cast<int16_t>(-Position);
      Position |= (1 << 15);
    }
    uint8_t bBuf[7];
    bBuf[0] = ACC;
    scserial_->host_2_scs(bBuf + 1, bBuf + 2, static_cast<uint16_t>(Position));
    scserial_->host_2_scs(bBuf + 3, bBuf + 4, 0);
    scserial_->host_2_scs(bBuf + 5, bBuf + 6, Speed);

    return scserial_->reg_write(ID, SMS_STS_ACC, bBuf, 7);
  }

  void sync_write_pos_ex(uint8_t ID[], uint8_t IDN, int16_t Position[],
                         uint16_t Speed[],
                         uint8_t ACC[]) // 同步写多个舵机位置指令
  {
    uint8_t *offbuf = new uint8_t[7 * IDN];
    for (uint8_t i = 0; i < IDN; i++) {
      if (Position[i] < 0) {
        Position[i] = static_cast<int16_t>(-Position[i]);
        Position[i] |= (1 << 15);
      }
      uint16_t V;
      if (Speed) {
        V = Speed[i];
      } else {
        V = 0;
      }
      if (ACC) {
        offbuf[i * 7] = ACC[i];
      } else {
        offbuf[i * 7] = 0;
      }
      scserial_->host_2_scs(offbuf + i * 7 + 1, offbuf + i * 7 + 2,
                            static_cast<uint16_t>(Position[i]));
      scserial_->host_2_scs(offbuf + i * 7 + 3, offbuf + i * 7 + 4, 0);
      scserial_->host_2_scs(offbuf + i * 7 + 5, offbuf + i * 7 + 6, V);
    }
    scserial_->sync_write(ID, IDN, SMS_STS_ACC, offbuf, 7);
    delete[] offbuf;
  }

  int rotation_mode(uint8_t ID) {
    return scserial_->write_byte(ID, SMS_STS_MODE, 0);
  }

  int wheel_mode(uint8_t ID) // 恒速模式
  {
    return scserial_->write_byte(ID, SMS_STS_MODE, 1);
  }

  int open_loop_wheel_mode(uint8_t ID) {
    return scserial_->write_byte(ID, SMS_STS_MODE, 2);
  }

  int write_speed(uint8_t ID, int16_t Speed,
                  uint8_t ACC = 0) // 恒速模式控制指令
  {
    if (Speed < 0) {
      Speed = static_cast<int16_t>(-Speed);
      Speed |= (1 << 15);
    }
    uint8_t bBuf[2];
    bBuf[0] = ACC;
    scserial_->gen_write(ID, SMS_STS_ACC, bBuf, 1);
    scserial_->host_2_scs(bBuf + 0, bBuf + 1, static_cast<uint16_t>(Speed));

    return scserial_->gen_write(ID, SMS_STS_GOAL_SPEED_L, bBuf, 2);
  }
  // ... 나머지 함수들 유지 (캐스팅 문제 없으면)

  int enable_torque(uint8_t ID, uint8_t Enable) // 扭力控制指令
  {
    return scserial_->write_byte(ID, SMS_STS_TORQUE_ENABLE, Enable);
  }

  int unlock_eprom(uint8_t ID) // eprom解锁
  {
    return scserial_->write_byte(ID, SMS_STS_LOCK, 0);
  }

  int lock_eprom(uint8_t ID) // eprom加锁
  {
    return scserial_->write_byte(ID, SMS_STS_LOCK, 1);
  }

  int calibration_offset(uint8_t ID) // 中位校准
  {
    return scserial_->write_byte(ID, SMS_STS_TORQUE_ENABLE, 128);
  }

  int feedback(int ID) // 反馈舵机信息
  {
    int nLen =
        scserial_->read(ID, SMS_STS_PRESENT_POSITION_L, Mem, sizeof(Mem));
    if (nLen != sizeof(Mem)) {
      err_ = 1;
      return -1;
    }
    err_ = 0;
    return nLen;
  }

  int read_position(int ID) // 读位置
  {
    int Pos = -1;
    if (ID == -1) {
      Pos = Mem[SMS_STS_PRESENT_POSITION_H - SMS_STS_PRESENT_POSITION_L];
      Pos <<= 8;
      Pos |= Mem[SMS_STS_PRESENT_POSITION_L - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Pos = scserial_->read_word(ID, SMS_STS_PRESENT_POSITION_L);
      if (Pos == -1) {
        err_ = 1;
      }
    }
    if (!err_ && (Pos & (1 << 15))) {
      Pos = -(Pos & ~(1 << 15));
    }

    return Pos;
  }

  int read_speed(int ID) // 读速度
  {
    int Speed = -1;
    if (ID == -1) {
      Speed = Mem[SMS_STS_PRESENT_SPEED_H - SMS_STS_PRESENT_POSITION_L];
      Speed <<= 8;
      Speed |= Mem[SMS_STS_PRESENT_SPEED_L - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Speed = scserial_->read_word(ID, SMS_STS_PRESENT_SPEED_L);
      if (Speed == -1) {
        err_ = 1;
        return -1;
      }
    }
    if (!err_ && (Speed & (1 << 15))) {
      Speed = -(Speed & ~(1 << 15));
    }
    return Speed;
  }

  int read_load(int ID) // 读输出至电机的电压百分比(0~1000)
  {
    int Load = -1;
    if (ID == -1) {
      Load = Mem[SMS_STS_PRESENT_LOAD_H - SMS_STS_PRESENT_POSITION_L];
      Load <<= 8;
      Load |= Mem[SMS_STS_PRESENT_LOAD_L - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Load = scserial_->read_word(ID, SMS_STS_PRESENT_LOAD_L);
      if (Load == -1) {
        err_ = 1;
      }
    }
    if (!err_ && (Load & (1 << 10))) {
      Load = -(Load & ~(1 << 10));
    }
    return Load;
  }

  int read_voltage(int ID) // 读电压
  {
    int Voltage = -1;
    if (ID == -1) {
      Voltage = Mem[SMS_STS_PRESENT_VOLTAGE - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Voltage = scserial_->read_byte(ID, SMS_STS_PRESENT_VOLTAGE);
      if (Voltage == -1) {
        err_ = 1;
      }
    }
    return Voltage;
  }

  double read_voltage_double(int ID) { return read_voltage(ID) / 10.0; }

  int read_temperature(int ID) // 读温度
  {
    int Temper = -1;
    if (ID == -1) {
      Temper = Mem[SMS_STS_PRESENT_TEMPERATURE - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Temper = scserial_->read_byte(ID, SMS_STS_PRESENT_TEMPERATURE);
      if (Temper == -1) {
        err_ = 1;
      }
    }
    return Temper;
  }

  int read_move(int ID) // 读移动状态
  {
    int Move = -1;
    if (ID == -1) {
      Move = Mem[SMS_STS_MOVING - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Move = scserial_->read_byte(ID, SMS_STS_MOVING);
      if (Move == -1) {
        err_ = 1;
      }
    }
    return Move;
  }

  int read_current(int ID) // 读电流
  {
    int Current = -1;
    if (ID == -1) {
      Current = Mem[SMS_STS_PRESENT_CURRENT_H - SMS_STS_PRESENT_POSITION_L];
      Current <<= 8;
      Current |= Mem[SMS_STS_PRESENT_CURRENT_L - SMS_STS_PRESENT_POSITION_L];
    } else {
      err_ = 0;
      Current = scserial_->read_word(ID, SMS_STS_PRESENT_CURRENT_L);
      if (Current == -1) {
        err_ = 1;
        return -1;
      }
    }
    if (!err_ && (Current & (1 << 15))) {
      Current = -(Current & ~(1 << 15));
    }
    return Current;
  }

  int read_goal(int ID) // 读电流
  {
    int Goal = -1;
    {
      err_ = 0;
      Goal = scserial_->read_word(ID, SMS_STS_GOAL_POSITION_L);
      if (Goal == -1) {
        err_ = 1;
        return -1;
      }
    }
    if (!err_ && (Goal & (1 << 15))) {
      Goal = -(Goal & ~(1 << 15));
    }
    return Goal;
  }

private:
  int err_ = 0;
  SCSerial *scserial_;
  uint8_t Mem[SMS_STS_PRESENT_CURRENT_H - SMS_STS_PRESENT_POSITION_L + 1];
};

} // namespace feetech_servo
