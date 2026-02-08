# FT SCServo Qt6 DDS - Implementation Plan

## 프로젝트 개요

**목표**: FT SCServo 설정 및 제어를 위한 Windows 전용 GUI 도구 개발

**아키텍처**: Daemon과 GUI가 **완전히 분리**되어 **RTI Connext DDS**로 통신

**참조 프로젝트**:
- `pingpong-base`: RTI DDS + Qt6 QML 통신 구조
- `scservo-ref`: FT SCServo 라이브러리 및 기존 GUI 기능

---

## 시스템 아키텍처

```
┌─────────────────────────────────────────────────────────────────────────┐
│                           FT SCServo System                             │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌──────────────────────┐         DDS          ┌──────────────────────┐ │
│  │      ServoGUI        │◄──────────────────►  │    ServoDaemon       │ │
│  │  (Qt6 QML 1280x720)  │                      │  (터미널 앱)           │ │
│  │                      │                      │                      │ │
│  │  - 연결 설정 UI       │  ServoCommand Topic  │  - Serial Port 관리   │ │
│  │  - 서보 리스트 표시   │  ─────────────────►  │  - SCServo 프로토콜   │ │
│  │  - 실시간 제어 패널   │                      │  - 명령 처리          │ │
│  │  - 피드백 그래프     │  ServoFeedback Topic │  - 피드백 수집         │ │
│  │  - 메모리 테이블     │  ◄─────────────────  │                      │ │
│  │                      │                      │                      │ │
│  │                      │  DaemonStatus Topic  │                      │ │
│  │                      │  ◄─────────────────  │                      │ │
│  └──────────────────────┘                      └──────────────────────┘ │
│                                                          │              │
│                                                          ▼              │
│                                                ┌──────────────────────┐ │
│                                                │   Serial Port        │ │
│                                                │   (CH340 Driver)     │ │
│                                                └──────────────────────┘ │
│                                                          │              │
│                                                          ▼              │
│                                                ┌──────────────────────┐ │
│                                                │   Feetech Servos     │ │
│                                                │   (SCS/STS/SMS/SMBL) │ │
│                                                └──────────────────────┘ │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## DDS Topics 설계

### 1. ServoCommand (GUI → Daemon)
```idl
struct ServoCommand {
    string command_type;      // "connect", "disconnect", "search", "write_pos", 
                              // "sync_write", "reg_write", "action", "set_torque",
                              // "read_memory", "write_memory", "sweep", "step"
    
    // 연결 정보
    string port_name;         // COM 포트 이름
    int32 baud_rate;          // 보드레이트
    int32 parity;             // 패리티 (0=NONE, 1=ODD, 2=EVEN)
    int32 timeout_ms;         // 타임아웃
    
    // 서보 제어
    int32 servo_id;           // 대상 서보 ID
    int32 goal_position;      // 목표 위치
    int32 speed;              // 속도
    int32 acceleration;       // 가속도
    int32 time_ms;            // 시간 (ms)
    
    // 메모리 접근
    int32 memory_address;     // 메모리 주소
    int32 memory_value;       // 쓸 값
    int32 memory_size;        // 1 또는 2 바이트
    
    // 토크
    boolean torque_enable;    // 토크 활성화
    
    int64 timestamp;          // 타임스탬프
};
```

### 2. ServoFeedback (Daemon → GUI)
```idl
struct ServoInfo {
    int32 id;                 // 서보 ID
    string model_name;        // 모델명 (예: "STS3215")
    string series;            // 시리즈 (SCS, STS, SMBL, SMCL)
};

struct ServoStatus {
    int32 id;                 // 서보 ID
    int32 position;           // 현재 위치
    int32 speed;              // 현재 속도
    int32 load;               // 부하
    int32 voltage;            // 전압 (0.1V 단위)
    int32 temperature;        // 온도
    int32 current;            // 전류
    int32 goal;               // 목표 위치
    boolean moving;           // 이동 중 여부
};

struct MemoryEntry {
    int32 address;
    string name;
    int32 value;
    boolean is_eprom;
    boolean is_readonly;
};

struct ServoFeedback {
    string feedback_type;     // "servo_found", "servo_status", "memory_data", 
                              // "search_progress", "search_complete", "error"
    
    sequence<ServoInfo> servos;        // 검색된 서보 목록
    ServoStatus status;                // 서보 상태
    sequence<MemoryEntry> memory;      // 메모리 데이터
    
    int32 search_progress;    // 검색 진행률 (0-253)
    string error_message;     // 에러 메시지
    
    int64 timestamp;
};
```

### 3. DaemonStatus (Daemon → GUI)
```idl
struct DaemonStatus {
    boolean connected;        // 시리얼 연결 상태
    string port_name;         // 현재 연결된 포트
    int32 baud_rate;          // 현재 보드레이트
    
    sequence<string> available_ports;  // 사용 가능한 포트 목록
    
    boolean searching;        // 서보 검색 중 여부
    int32 servo_count;        // 발견된 서보 수
    
    int64 timestamp;
};
```

---

## Phase별 구현 계획

### Phase 1: 프로젝트 기반 구조 (Foundation)
**목표**: DDS 통신 기반의 Daemon-GUI 분리 아키텍처 구축

**작업 내용**:
1. 프로젝트 디렉토리 구조 생성
2. CMakeLists.txt 설정 (RTI DDS + Qt6)
3. IDL 파일 정의 및 코드 생성
4. QoS 프로파일 설정 (USER_QOS_PROFILES.xml)
5. 빌드/실행 스크립트 작성

**산출물**:
```
ft-scservo-qt6-dds/
├── CMakeLists.txt
├── scservo.idl
├── USER_QOS_PROFILES.xml
├── build.ps1
├── run.ps1
├── servo/                  # SCServo 라이브러리 (scservo-ref에서 복사)
│   ├── scserial.h/cpp
│   ├── servo_types.h
│   ├── sms_sts.h
│   └── scscl.h
├── daemon/
│   └── main.cpp           # 빈 스켈레톤
├── gui/
│   ├── main.cpp           # 빈 스켈레톤
│   ├── DdsManager.hpp/cpp
│   └── Main.qml           # 1280x720 기본 레이아웃
└── gen/                   # rtiddsgen 생성 코드
```

---

### Phase 2: Daemon 개발 (Serial + DDS)
**목표**: 시리얼 통신 및 DDS 퍼블리싱 기능 구현

**작업 내용**:
1. **SerialManager 클래스**
   - 포트 스캔 및 열기/닫기
   - SCSerial/SCSCL/SMS_STS 래퍼
   
2. **CommandHandler 클래스**
   - ServoCommand 구독 및 처리
   - 명령 타입별 동작 분기
   
3. **FeedbackPublisher 클래스**
   - 서보 상태 주기적 발행
   - 이벤트 발생 시 즉시 발행
   
4. **DaemonStatusPublisher**
   - 연결 상태, 포트 목록 발행

**Daemon 동작 흐름**:
```
1. 시작 → DaemonStatus 발행 (미연결, 포트 목록)
2. "connect" 명령 수신 → 시리얼 연결 → DaemonStatus 업데이트
3. "search" 명령 수신 → ID 0~253 스캔 → ServoFeedback 발행
4. "write_pos" 명령 수신 → 서보 제어 → 결과 피드백
5. 주기적 (10ms) → 선택된 서보 상태 읽기 → ServoFeedback 발행
```

---

### Phase 3: GUI 기본 레이아웃 (Qt6 QML)
**목표**: 1280x720 모던 UI 레이아웃 구현

**해상도**: **1280 x 720**

**레이아웃 설계**:
```
┌─────────────────────────────────────────────────────────────────────┐
│  FT SCServo Qt6 Control Panel                          [─] [□] [×] │
├─────────────────────────────────────────────────────────────────────┤
│ ┌──────────────┐ ┌──────────────────────────────────────────────┐  │
│ │ Connection   │ │                                              │  │
│ │ ┌──────────┐ │ │              Real-time Graph                 │  │
│ │ │ COM Port │ │ │         (Position, Speed, Load)              │  │
│ │ │ Baud Rate│ │ │                                              │  │
│ │ │ [Connect]│ │ │                                              │  │
│ │ └──────────┘ │ └──────────────────────────────────────────────┘  │
│ ├──────────────┤ ┌─────────────────────┐ ┌──────────────────────┐  │
│ │ Servo List   │ │   Servo Control     │ │   Servo Feedback     │  │
│ │              │ │                     │ │                      │  │
│ │  ID │ Model  │ │  [═══════════○════] │ │  Position: 2047      │  │
│ │ ────┼─────── │ │  Goal: 2047         │ │  Speed:    0         │  │
│ │  1  │ STS3215│ │  Speed: 0  Acc: 0   │ │  Load:     0%        │  │
│ │  2  │ STS3032│ │  Time: 0            │ │  Voltage:  7.4V      │  │
│ │              │ │                     │ │  Temp:     25°C      │  │
│ │  [Search]    │ │  ○Write ○Sync ○Reg  │ │  Current:  0mA       │  │
│ │              │ │  [Set] [Action]     │ │  Moving:   No        │  │
│ └──────────────┘ └─────────────────────┘ └──────────────────────┘  │
│ ┌───────────────────────────────────────────────────────────────┐  │
│ │ Tabs: [Debug] [Memory] [Auto Test]                            │  │
│ │                                                               │  │
│ │  Memory Table / Auto Debug Controls                           │  │
│ │                                                               │  │
│ └───────────────────────────────────────────────────────────────┘  │
├─────────────────────────────────────────────────────────────────────┤
│  Status: Connected to COM3 @ 1000000 | 2 servos found | Ready      │
└─────────────────────────────────────────────────────────────────────┘
```

**QML 컴포넌트 구조**:
```
Main.qml (1280x720)
├── components/
│   ├── ConnectionPanel.qml    # 연결 설정
│   ├── ServoListPanel.qml     # 서보 목록
│   ├── ControlPanel.qml       # 서보 제어
│   ├── FeedbackPanel.qml      # 실시간 피드백
│   ├── GraphPanel.qml         # 그래프
│   ├── MemoryPanel.qml        # 메모리 테이블
│   └── AutoDebugPanel.qml     # 자동 디버그
└── style/
    └── Theme.qml              # 다크 테마 스타일
```

---

### Phase 4: GUI-DDS 통합
**목표**: GUI에서 DDS를 통해 Daemon과 통신

**작업 내용**:
1. **DdsManager 클래스**
   - ServoCommand 발행
   - ServoFeedback/DaemonStatus 구독
   - Qt 시그널로 QML에 전달

2. **QML 바인딩**
   - 포트 목록 → ComboBox
   - 서보 목록 → ListView
   - 서보 상태 → 레이블/그래프

3. **이벤트 처리**
   - Connect 버튼 → sendCommand("connect")
   - Search 버튼 → sendCommand("search")
   - 슬라이더 변경 → sendCommand("write_pos")

---

### Phase 5: 고급 기능 구현
**목표**: 메모리 편집, 자동 디버그, 데이터 기록

**작업 내용**:
1. **Memory Panel**
   - 메모리 테이블 표시 (주소, 이름, 값, EPROM/SRAM, R/W)
   - 값 편집 및 쓰기

2. **Auto Debug**
   - Sweep 모드 (시작↔끝 반복)
   - Step 모드 (증분 이동)

3. **Data Recording**
   - CSV 파일로 피드백 데이터 저장
   - 기록 시작/중지

---

### Phase 6: 폴리싱 및 최적화
**목표**: UI 개선, 에러 처리, 문서화

**작업 내용**:
1. **UI 개선**
   - 애니메이션 및 전환 효과
   - 아이콘 및 시각적 피드백
   - 반응형 레이아웃

2. **에러 처리**
   - 연결 실패/끊김 처리
   - 서보 통신 오류 처리
   - 사용자 친화적 에러 메시지

3. **문서화**
   - README.md
   - 사용자 가이드
   - 빌드 가이드

---

## 기술 스택

| 구성 요소 | 기술 |
|---------|-----|
| C++ 표준 | C++17 |
| 빌드 시스템 | CMake 3.16+ |
| DDS 미들웨어 | RTI Connext DDS 7.5.0 |
| GUI 프레임워크 | Qt6 (QML/Quick) |
| 시리얼 통신 | Qt6 SerialPort |
| 컴파일러 | MSVC (Visual Studio 2017+) |
| 플랫폼 | Windows 10/11 (x64) |

---

## 파일 구조 (최종)

```
ft-scservo-qt6-dds/
├── CMakeLists.txt
├── README.md
├── build.ps1
├── run.ps1
├── scservo.idl                    # DDS 데이터 타입 정의
├── USER_QOS_PROFILES.xml          # QoS 프로파일
│
├── servo/                          # Feetech Servo 라이브러리
│   ├── scserial.h
│   ├── scserial.cpp
│   ├── servo_types.h
│   ├── sms_sts.h
│   └── scscl.h
│
├── daemon/                         # 서보 제어 데몬
│   ├── main.cpp
│   ├── SerialManager.hpp/cpp
│   ├── CommandHandler.hpp/cpp
│   └── FeedbackPublisher.hpp/cpp
│
├── gui/                            # Qt6 QML GUI
│   ├── main.cpp
│   ├── DdsManager.hpp/cpp
│   ├── Main.qml
│   ├── components/
│   │   ├── ConnectionPanel.qml
│   │   ├── ServoListPanel.qml
│   │   ├── ControlPanel.qml
│   │   ├── FeedbackPanel.qml
│   │   ├── GraphPanel.qml
│   │   ├── MemoryPanel.qml
│   │   └── AutoDebugPanel.qml
│   └── style/
│       └── Theme.qml
│
└── gen/                            # rtiddsgen 생성 코드
    ├── scservo.cxx
    ├── scservo.hpp
    ├── scservoPlugin.cxx
    └── scservoPlugin.hpp
```

---

## 마일스톤

| Phase | 예상 작업량 | 산출물 |
|-------|-----------|-------|
| **Phase 1** | 기반 구조 | 빌드 가능한 스켈레톤 |
| **Phase 2** | Daemon | 시리얼 통신 + DDS 발행 동작 |
| **Phase 3** | GUI 레이아웃 | 1280x720 UI 렌더링 |
| **Phase 4** | 통합 | GUI ↔ Daemon 통신 동작 |
| **Phase 5** | 고급 기능 | 메모리 편집, 자동 디버그 |
| **Phase 6** | 폴리싱 | 최종 릴리스 |

---

## 다음 단계

**Phase 1 구현 준비 완료?**
- [ ] 사용자 확인 후 Phase 1 구현 시작
