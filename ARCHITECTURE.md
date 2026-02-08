# System Architecture

## Overview
The **FT SCServo Qt6 DDS Control** system is designed with a decoupled architecture to ensure stability, scalability, and responsiveness. It consists of two main applications communicating via **RTI Connext DDS**.

1.  **ServoGUI**: A Qt6/QML-based user interface for control and monitoring.
2.  **ServoDaemon**: A robust C++ console application handling hardware communication and real-time control.

---

## Architecture Diagram

The following diagram illustrates the high-level architecture and data flow between components.

```mermaid
graph TD
    %% Subgraphs for Logical Grouping
    subgraph "User Layer"
        User((User))
    end

    subgraph "ServoGUI (Qt6 Application)"
        QML["QML UI Layer"]
        Bridge["DdsManager (C++)"]
    end

    subgraph "RTI Connext DDS (Middleware)"
        TopicCmd("Topic: ServoCommand")
        TopicFb("Topic: ServoFeedback")
    end

    subgraph "ServoDaemon (C++ Console App)"
        Daemon["ServoDaemon Core"]
        Lib["SCServo Library"]
        Serial["Custom SerialPort (WinAPI)"]
    end

    subgraph "Hardware Layer"
        Motor["FT SCServo Motor"]
    end

    %% Interactions
    User -->|Interacts| QML
    QML <-->|Signals/Slots| Bridge
    
    %% DDS Communication
    Bridge -->|Publish| TopicCmd
    TopicCmd -->|Subscribe| Daemon
    
    Daemon -->|Publish| TopicFb
    TopicFb -->|Subscribe| Bridge

    %% Hardware Control
    Daemon -->|Calls| Lib
    Lib -->|Uses| Serial
    Serial <-->|UART/RS485| Motor

    %% Styling
    style TopicCmd fill:#f9f,stroke:#333,stroke-width:2px
    style TopicFb fill:#bbf,stroke:#333,stroke-width:2px
    style Daemon fill:#dfd,stroke:#333,stroke-width:2px
    style Bridge fill:#ddf,stroke:#333,stroke-width:2px
```

---

## Data Flow (Sequence)

This sequence diagram depicts the flow of a **Connect** command and the periodic **Heartbeat** mechanism.

```mermaid
sequenceDiagram
    participant User
    participant GUI as ServoGUI (DdsManager)
    participant DDS as RTI Connext DDS
    participant Daemon as ServoDaemon
    participant HW as SCServo HW

    Note over User, GUI: 1. Connection Request
    User->>GUI: Click "Connect" Button
    GUI->>DDS: Write(ServoCommand::Connect, Port="COM3")
    
    Note over DDS, Daemon: 2. Command Processing
    DDS->>Daemon: OnDataAvailable()
    Daemon->>Daemon: processCommand()
    Daemon->>HW: SerialPort::open("COM3")
    
    alt Success
        HW-->>Daemon: Port Opened
        Daemon->>DDS: Write(ServoFeedback::Status, "Connected")
        DDS->>GUI: OnDataAvailable()
        GUI->>User: Update UI (Green LED)
    else Failure
        HW-->>Daemon: Error
        Daemon->>DDS: Write(ServoFeedback::Error, "Failed")
        DDS->>GUI: OnDataAvailable()
        GUI->>User: Show Error Message
    end

    Note over Daemon, GUI: 3. Periodic Heartbeat (Every 1s)
    loop Background Thread
        Daemon->>DDS: Write(ServoFeedback::Ping, "Heartbeat #N")
        DDS->>GUI: OnDataAvailable()
        GUI->>GUI: Reset Watchdog / Log
    end
```

---

## Component Details

### 1. ServoGUI (Qt6)
*   **Main.qml**: Defines the visual layout using Qt Quick Controls 2. Handles user input (buttons, sliders) and displays status.
*   **DdsManager**: A C++ class inheriting `QObject`.
    *   Exposes `sendConnect()`, `sendPing()` to QML.
    *   Updates QML properties (`status`, `messages`) upon receiving DDS data.
    *   Implements a Watchdog to detect Daemon disconnection if Heartbeats stop.

### 2. ServoDaemon (C++)
*   **ServoDaemon**: The core class managing the application lifecycle.
    *   Initializes DDS participants/writers/readers.
    *   Maintains a `run()` loop for periodic tasks (Heartbeat).
    *   Implements `processCommand()` to dispatch incoming requests.
*   **SCServo Library**:
    *   `SMS_STS`: Protocol implementation for SCServo.
    *   `SCSerial`: Handles packet serialization.
*   **SerialPort**:
    *   A custom, lightweight C++ wrapper around Windows API (`CreateFile`, `ReadFile`, `WriteFile`) to avoid Qt dependencies in the Daemon.

### 3. DDS Topics (IDL)
Defined in `scservo.idl`:

*   **ServoCommand**:
    *   `command_type` (string): "connect", "disconnect", "ping", "write_pos", "shutdown"
    *   `value` (long): Generic value (Ping ID, Position, etc.)
    *   `speed`, `acc`: Motion parameters.

*   **ServoFeedback**:
    *   `feedback_type` (string): "pong", "status", "error", "ping"
    *   `message` (string): Human-readable message.
    *   `is_error` (boolean): Error flag.
    *   `connected` (boolean): Hardware connection state.

---

## Directory Structure

```
/
├── daemon/             # Daemon Source Code
│   ├── servo/          # SCServo Control Library
│   ├── SerialPort.hpp  # Custom Serial Port Wrapper
│   ├── ServoDaemon.hpp # Main Daemon Logic
│   └── main.cpp        # Entry Point
├── gui/                # Qt GUI Source Code
│   ├── DdsManager.hpp  # DDS Bridge for QML
│   └── main.cpp        # Qt Entry Point
├── gen/                # RTI DDS Generated Code (IDL)
├── scservo.idl         # DDS Interface Definition
├── Main.qml            # GUI Layout
├── build.ps1           # Build Script
└── run.ps1             # Execution Script
```
