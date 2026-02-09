# SCServo Protocol Specification

## Overview

This protocol applies to the Feetech STS3215 and similar servo motors used in the project. The information below details the memory register map, communication parameters, and hardware specifications.

### Key Specifications (STS3215)
- **Resolution**: 4096 steps per revolution
- **Maximum Effective Angle**: 360 degrees
- **Minimum Resolution Angle**: 0.087890625 degrees/step
- **No-load Speed**: 50 RPM (3400 steps/second) @ 7.4V
- **No-load Current**: 150 mA @ 7.4V
- **Electronic Dead Zone**: 0.17578125 degrees
- **Acceleration**: 8.7890625 degrees/s^2 (per unit step?) *Note: See register 0x29 for acceleration setting details.*
- **Control Mode**: Supports multi-turn large-angle control (does not retain revolution count after power loss).

### Reference
- [Official Register Map (Excel)](https://files.waveshare.com/upload/2/27/ST3215%20memory%20register%20map-EN.xls)

---

## Memory Map

### EPROM (Non-Volatile Memory)
| Address | Name | value | Min | Max | Unit | Access | Description |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **0x00** | Firmware Major Version | - | - | - | - | Read | 펌웨어 메이저 버전 번호 |
| **0x01** | Firmware Minor Version | - | - | - | - | Read | 펌웨어 마이너 버전 번호 |
| **0x03** | Servo Major Version | - | - | - | - | Read | 서보 메이저 버전 번호 |
| **0x04** | Servo Minor Version | - | - | - | - | Read | 서보 마이너 버전 번호 |
| **0x05** | ID | 1 | 0 | 253 | - | R/W | 버스 상의 고유 식별 코드. 254(0xFE)는 브로드캐스트 ID. |
| **0x06** | Baud Rate | 0 | 0 | 7 | - | R/W | 0~7: 1M, 500K, 250K, 128K, 115200, 76800, 57600, 38400 |
| **0x07** | Return Delay | 0 | 0 | 254 | 2us | R/W | 응답 지연 시간. 최대 508us (254*2). |
| **0x08** | Response Status Level | 1 | 0 | 1 | - | R/W | 0: Read/PING 외 응답 없음, 1: 모든 명령에 응답. |
| **0x09** | Minimum Angle Limit | 0 | -32766 | - | Step | R/W | 동작 범위 최소값. 멀티턴 모드 시 0. |
| **0x0B** | Maximum Angle Limit | 4095 | - | 32767 | Step | R/W | 동작 범위 최대값. 멀티턴 모드 시 0. |
| **0x0D** | Max Temperature | 70 | 0 | 100 | °C | R/W | 최대 작동 온도 제한. |
| **0x0E** | Max Input Voltage | 80 | 0 | 254 | 0.1V | R/W | 최대 입력 전압 제한. 예: 80 -> 8.0V. |
| **0x0F** | Min Input Voltage | 40 | 0 | 254 | 0.1V | R/W | 최소 입력 전압 제한. 예: 40 -> 4.0V. |
| **0x10** | Max Torque | 1000 | 0 | 1000 | 0.1% | R/W | 최대 출력 토크 제한. 1000은 100%. |
| **0x12** | Phase | 0 | 0 | 254 | - | R/W | 특수 기능 바이트. 수정 주의. |
| **0x13** | Unloading Conditions | 0 | 0 | 254 | - | R/W | 비트 설정 시 해당 보호 활성화 (Voltage, Sensor, Temp, Current, Angle, Overload). |
| **0x14** | LED Alarm Conditions | 0 | 0 | 254 | - | R/W | 비트 설정 시 해당 LED 깜빡임 활성화. |
| **0x15** | Position P Coefficient | 32 | 0 | 254 | - | R/W | 위치 제어 비례(P) 계수. |
| **0x16** | Position D Coefficient | 32 | 0 | 254 | - | R/W | 위치 제어 미분(D) 계수. |
| **0x17** | Position I Coefficient | 0 | 0 | 254 | - | R/W | 위치 제어 적분(I) 계수. |
| **0x18** | Min Starting Force | 16 | 0 | 1000 | 0.1% | R/W | 최소 시동 토크. |
| **0x1A** | CW Dead Zone | 1 | 0 | 32 | Step | R/W | 시계 방향 불감도 영역. |
| **0x1B** | CCW Dead Zone | 1 | 0 | 32 | Step | R/W | 반시계 방향 불감도 영역. |
| **0x1C** | Protection Current | 500 | 0 | 511 | 6.5mA | R/W | 과전류 보호 제한. 500 * 6.5mA = 3250mA. |
| **0x1E** | Angle Resolution | 1 | 1 | 3 | - | R/W | 센서 분해능 증폭 계수. 멀티턴 제어 시 0x12 BIT4=1 필요. |
| **0x1F** | Position Correction | 0 | -2047 | 2047 | Step | R/W | 위치 보정값. |
| **0x21** | Operation Mode | 0 | 0 | 3 | - | R/W | 0: 위치, 1: 정속(0x2E), 2: PWM 오픈루프(0x2C), 3: 스텝(0x2A). |
| **0x22** | Protection Torque | 20 | 0 | 100 | 1% | R/W | 과부하 보호 진입 후 출력 토크. |
| **0x23** | Protection Time | 200 | 0 | 254 | 10ms | R/W | 과부하 지속 허용 시간. |
| **0x24** | Overload Torque | 80 | 0 | 100 | 1% | R/W | 과부하 보호 시작 토크 임계값. |
| **0x25** | Speed P Coefficient | 10 | 0 | 100 | - | R/W | 정속 모드 속도 루프 P 계수. |
| **0x26** | Overcurrent Time | 200 | 0 | 254 | 10ms | R/W | 과전류 보호 시간. |
| **0x27** | Speed I Coefficient | 10 | 0 | 254 | - | R/W | 정속 모드 속도 루프 I 계수. |

### SRAM (Volatile Memory)
| Address | Name | Initial | Min | Max | Unit | Access | Description |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **0x28** | Torque Switch | 0 | 0 | 128 | - | R/W | 0: Off, 1: On, 128: 현재 위치를 2048로 보정. |
| **0x29** | Acceleration | 0 | 0 | 254 | - | R/W | 가속도. 10 -> 1000 step/s^2. |
| **0x2A** | Target Location | 0 | -30719 | 30719 | Step | R/W | 목표 위치 (절대 위치 모드). |
| **0x2C** | Operation Time | 0 | 0 | 1000 | - | R/W | PWM 오픈루프 모드 운전 시간. |
| **0x2E** | Operation Speed | 0 | 0 | 3400 | step/s | R/W | 운전 속도. 50 step/s = 0.732 RPM. |
| **0x30** | Torque Limit | 1000 | 0 | 1000 | 0.1% | R/W | 토크 제한. 초기값은 Max Torque(0x10). |
| **0x37** | Lock Flag | 0 | 0 | 1 | - | R/W | 0: Unlock, 1: Lock (EPROM 저장 방지). |
| **0x38** | Current Location | - | - | - | Step | Read | 현재 위치 피드백. |
| **0x3A** | Current Speed | - | - | - | step/s | Read | 현재 속도 피드백. |
| **0x3C** | Current Load | - | - | - | 0.1% | Read | 현재 부하 (전압 듀티 사이클). |
| **0x3E** | Current Voltage | - | - | - | 0.1V | Read | 현재 전압. |
| **0x3F** | Current Temperature | - | - | - | °C | Read | 현재 온도. |
| **0x40** | Async Write Flag | - | - | - | - | Read | 비동기 쓰기 플래그. |
| **0x41** | Servo Status | - | - | - | - | Read | 에러 상태 비트. |
| **0x42** | Move Flag | - | - | - | - | Read | 1: 이동 중, 0: 정지. |
| **0x45** | Current Current | - | - | - | 6.5mA | Read | 현재 전류. |
