# FT SCServo Qt6 DDS Control

This project implements a control system for FT SCServo motors using RTI Connext DDS for communication and Qt6 for the graphical user interface.

## Architecture

- **ServoDaemon**: C++ Console Application acting as a DDS publisher/subscriber and hardware interface controller.
  - Controls SCServo motors via serial port.
  - Publishes `ServoFeedback` topics.
  - Subscribes to `ServoCommand` topics.
  - Implements a custom `SerialPort` class using Windows API (Qt-free).

- **ServoGUI**: Qt6 QML Application for user interaction.
  - Publishes `ServoCommand` topics (Connect, WritePos, Ping, Shutdown).
  - Subscribes to `ServoFeedback` topics (Position, Status, Heartbeat).

## Prerequisites

- **RTI Connext DDS 7.5.0** (with `NDDSHOME` environment variable set)
- **Qt 6.10.2** (MSVC 2022 64-bit)
- **Visual Studio 2022** (or Build Tools)
- **CMake 3.20+**

## Build & Run

Use the provided PowerShell scripts:

1. **Build**:
   ```powershell
   .\build.ps1
   ```
2. **Run**:
   ```powershell
   .\run.ps1
   ```
   This will launch both `ServoDaemon` and `ServoGUI`.

## Communication Protocol (DDS)

- **Topic: ServoCommand** (`scservo::ServoCommand`)
  - `command_type`: "connect", "disconnect", "ping", "write_pos", "shutdown"
  - `value`: Position or Ping ID
  - `speed`, `acc`: Control parameters

- **Topic: ServoFeedback** (`scservo::ServoFeedback`)
  - `feedback_type`: "pong", "status", "error", "ping" (Heartbeat)
  - `message`: Detailed info
  - `connected`: Daemon-Hardware connection status

## License & Third-Party Notices

### Qt Framework
This application uses the Qt 6 framework under the **LGPLv3 license**.
Qt is a registered trademark of The Qt Company Ltd. and its subsidiaries.
For more information, see [https://www.qt.io/](https://www.qt.io/) and [https://doc.qt.io/qt-6/lgpl.html](https://doc.qt.io/qt-6/lgpl.html).

### RTI Connext DDS
This application uses RTI Connext DDS. Please refer to RTI's license agreement for usage terms.

---
Copyright (c) 2026 This Project Contributors.
