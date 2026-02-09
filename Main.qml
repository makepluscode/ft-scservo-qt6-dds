/*
 * Main.qml - FT SCServo Qt6 DDS GUI
 * Based on feetech-servo-tool reference
 * 해상도: 1280 x 800
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 800
    visible: true
    title: "FT SCServo Tool - Qt6 DDS"
    color: bgColor

    // ========== 다크 테마 색상 ==========
    readonly property color bgColor: "#0f0f0f"
    readonly property color cardColor: "#1a1a1a"
    readonly property color cardHoverColor: "#252525"
    readonly property color accentColor: "#3b82f6"
    readonly property color successColor: "#22c55e"
    readonly property color warningColor: "#f59e0b"
    readonly property color errorColor: "#ef4444"
    readonly property color textPrimary: "#ffffff"
    readonly property color textSecondary: "#a0a0a0"
    readonly property color borderColor: "#333333"
    readonly property color inputBgColor: "#252525"

    // ========== 상태 변수 ==========
    property bool isConnected: false
    property bool isSearching: false
    property int selectedServoId: -1
    property var foundServos: []
    
    // 서보 상태
    property int servoPosition: 0
    property int servoGoal: 2048
    property int servoSpeed: 0
    property int servoLoad: 0
    property real servoVoltage: 0.0
    property int servoTemperature: 0
    property int servoCurrent: 0
    property bool servoMoving: false
    property bool torqueEnabled: false

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 12
        spacing: 12

        // ========== Header ==========
        Rectangle {
            Layout.fillWidth: true
            height: 50
            radius: 8
            color: cardColor
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 12
                spacing: 16

                // 연결 상태 LED
                Rectangle {
                    width: 12
                    height: 12
                    radius: 6
                    color: isConnected ? successColor : (ddsManager.daemonConnected ? warningColor : errorColor)
                    
                    SequentialAnimation on opacity {
                        running: !ddsManager.daemonConnected
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.4; duration: 500 }
                        NumberAnimation { to: 1.0; duration: 500 }
                    }
                }

                Text {
                    text: isConnected ? "Connected to Servo" : 
                          (ddsManager.daemonConnected ? "Daemon Ready" : "Waiting for Daemon...")
                    color: textPrimary
                    font.pixelSize: 14
                    font.weight: Font.Medium
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "FT SCServo Tool"
                    color: textSecondary
                    font.pixelSize: 14
                    font.weight: Font.Bold
                }
            }
        }

        // ========== Main Content ==========
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 12

            // ===== Left Column: COM Settings + Servo List =====
            ColumnLayout {
                Layout.preferredWidth: 280
                Layout.fillHeight: true
                spacing: 12

                // --- COM Settings Card ---
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 180
                    radius: 8
                    color: cardColor
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 10

                        Text {
                            text: "📡 COM Settings"
                            color: textPrimary
                            font.pixelSize: 14
                            font.weight: Font.Bold
                        }

                        Rectangle { Layout.fillWidth: true; height: 1; color: borderColor }

                        // Port Selection
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 8

                            Text { text: "Port:"; color: textSecondary; font.pixelSize: 12; Layout.preferredWidth: 50 }
                            ComboBox {
                                id: portCombo
                                Layout.fillWidth: true
                                model: ["COM1", "COM3", "COM6", "COM7"]
                                currentIndex: 2
                                enabled: !isConnected
                                
                                background: Rectangle {
                                    radius: 4
                                    color: inputBgColor
                                    border.color: borderColor
                                }
                                contentItem: Text {
                                    text: portCombo.displayText
                                    color: textPrimary
                                    font.pixelSize: 12
                                    verticalAlignment: Text.AlignVCenter
                                    leftPadding: 8
                                }
                            }
                        }

                        // Baud Rate
                        RowLayout {
                            Layout.fillWidth: true
                            spacing: 8

                            Text { text: "Baud:"; color: textSecondary; font.pixelSize: 12; Layout.preferredWidth: 50 }
                            ComboBox {
                                id: baudCombo
                                Layout.fillWidth: true
                                model: ["1000000", "500000", "250000", "115200", "57600", "38400", "19200", "9600"]
                                currentIndex: 0
                                enabled: !isConnected
                                
                                background: Rectangle {
                                    radius: 4
                                    color: inputBgColor
                                    border.color: borderColor
                                }
                                contentItem: Text {
                                    text: baudCombo.displayText
                                    color: textPrimary
                                    font.pixelSize: 12
                                    verticalAlignment: Text.AlignVCenter
                                    leftPadding: 8
                                }
                            }
                        }

                        // Connect Button
                        Button {
                            id: connectBtn
                            Layout.fillWidth: true
                            Layout.preferredHeight: 36
                            text: isConnected ? "🔌 Disconnect" : "🔗 Connect"
                            enabled: ddsManager.daemonConnected

                            background: Rectangle {
                                radius: 6
                                color: isConnected ? errorColor : 
                                       (connectBtn.pressed ? Qt.darker(successColor, 1.2) : 
                                        connectBtn.hovered ? Qt.lighter(successColor, 1.1) : successColor)
                                opacity: connectBtn.enabled ? 1.0 : 0.5
                            }

                            contentItem: Text {
                                text: connectBtn.text
                                color: textPrimary
                                font.pixelSize: 13
                                font.weight: Font.Medium
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            onClicked: {
                                if (isConnected) {
                                    ddsManager.sendDisconnect()
                                    isConnected = false
                                    foundServos = []
                                    selectedServoId = -1
                                } else {
                                    ddsManager.sendConnect(portCombo.currentText, parseInt(baudCombo.currentText))
                                    isConnected = true
                                }
                            }
                        }
                    }
                }

                // --- Servo List Card ---
                Rectangle {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    radius: 8
                    color: cardColor
                    border.color: borderColor
                    border.width: 1

                    ColumnLayout {
                        anchors.fill: parent
                        anchors.margins: 12
                        spacing: 10

                        RowLayout {
                            Layout.fillWidth: true

                            Text {
                                text: "🔍 Servo List"
                                color: textPrimary
                                font.pixelSize: 14
                                font.weight: Font.Bold
                            }

                            Item { Layout.fillWidth: true }

                            Text {
                                text: foundServos.length + " found"
                                color: textSecondary
                                font.pixelSize: 11
                            }
                        }

                        Rectangle { Layout.fillWidth: true; height: 1; color: borderColor }

                        // Search Status
                        Text {
                            id: searchStatus
                            text: isSearching ? "Scanning..." : "Ready"
                            color: isSearching ? warningColor : textSecondary
                            font.pixelSize: 11
                            visible: isConnected
                        }

                        // Servo List View
                        ListView {
                            id: servoListView
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            model: foundServos
                            clip: true
                            spacing: 4

                            delegate: Rectangle {
                                width: servoListView.width
                                height: 36
                                radius: 4
                                color: selectedServoId === modelData.id ? accentColor : 
                                       (delegateMA.containsMouse ? cardHoverColor : "transparent")
                                border.color: selectedServoId === modelData.id ? accentColor : borderColor
                                border.width: 1

                                MouseArea {
                                    id: delegateMA
                                    anchors.fill: parent
                                    hoverEnabled: true
                                    onClicked: {
                                        selectedServoId = modelData.id
                                        // 상태 읽기 시작
                                        readStateTimer.start()
                                    }
                                }

                                RowLayout {
                                    anchors.fill: parent
                                    anchors.margins: 8
                                    spacing: 12

                                    Text {
                                        text: "ID " + modelData.id
                                        color: selectedServoId === modelData.id ? textPrimary : textSecondary
                                        font.pixelSize: 12
                                        font.weight: Font.Medium
                                    }

                                    Text {
                                        text: modelData.model || "ST3215"
                                        color: selectedServoId === modelData.id ? textPrimary : textSecondary
                                        font.pixelSize: 11
                                    }
                                }
                            }

                            // Empty state
                            Text {
                                anchors.centerIn: parent
                                visible: foundServos.length === 0
                                text: isConnected ? "No servos found.\nClick Search." : "Connect first."
                                color: textSecondary
                                font.pixelSize: 12
                                horizontalAlignment: Text.AlignHCenter
                                opacity: 0.6
                            }
                        }

                        // Search Button
                        Button {
                            id: searchBtn
                            Layout.fillWidth: true
                            Layout.preferredHeight: 32
                            text: isSearching ? "⏹️ Stop" : "🔎 Search"
                            enabled: isConnected

                            background: Rectangle {
                                radius: 6
                                color: searchBtn.pressed ? Qt.darker(accentColor, 1.2) : 
                                       searchBtn.hovered ? Qt.lighter(accentColor, 1.1) : accentColor
                                opacity: searchBtn.enabled ? 1.0 : 0.5
                            }

                            contentItem: Text {
                                text: searchBtn.text
                                color: textPrimary
                                font.pixelSize: 12
                                horizontalAlignment: Text.AlignHCenter
                                verticalAlignment: Text.AlignVCenter
                            }

                            onClicked: {
                                if (isSearching) {
                                    isSearching = false
                                } else {
                                    isSearching = true
                                    foundServos = []
                                    ddsManager.sendScan()
                                    // 임시: 2초 후 더미 데이터
                                    scanTimer.start()
                                }
                            }
                        }
                    }
                }
            }

            // ===== Center Column: Servo Control + Status =====
            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                spacing: 12

                // --- Tab Bar ---
                TabBar {
                    id: tabBar
                    Layout.fillWidth: true
                    Layout.preferredHeight: 40

                    background: Rectangle {
                        color: cardColor
                        radius: 8
                    }

                    TabButton {
                        text: "🎮 Debug"
                        width: implicitWidth
                        
                        background: Rectangle {
                            color: tabBar.currentIndex === 0 ? accentColor : "transparent"
                            radius: 6
                        }
                        contentItem: Text {
                            text: parent.text
                            color: textPrimary
                            font.pixelSize: 13
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }

                    TabButton {
                        text: "⚙️ Programming"
                        width: implicitWidth
                        
                        background: Rectangle {
                            color: tabBar.currentIndex === 1 ? accentColor : "transparent"
                            radius: 6
                        }
                        contentItem: Text {
                            text: parent.text
                            color: textPrimary
                            font.pixelSize: 13
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }
                    }
                }

                // --- Tab Content ---
                StackLayout {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    currentIndex: tabBar.currentIndex

                    // ===== Debug Tab =====
                    RowLayout {
                        spacing: 12

                        // --- Servo Control ---
                        Rectangle {
                            Layout.preferredWidth: 300
                            Layout.fillHeight: true
                            radius: 8
                            color: cardColor
                            border.color: borderColor
                            border.width: 1

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 12
                                spacing: 12

                                Text {
                                    text: "🎛️ Servo Control"
                                    color: textPrimary
                                    font.pixelSize: 14
                                    font.weight: Font.Bold
                                }

                                Rectangle { Layout.fillWidth: true; height: 1; color: borderColor }

                                // Mode Selection
                                RowLayout {
                                    Layout.fillWidth: true
                                    spacing: 8

                                    RadioButton {
                                        id: writeMode
                                        text: "Write"
                                        checked: true
                                        
                                        contentItem: Text {
                                            text: parent.text
                                            color: textSecondary
                                            font.pixelSize: 11
                                            leftPadding: parent.indicator.width + 4
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                    }
                                    RadioButton {
                                        id: syncMode
                                        text: "Sync"
                                        
                                        contentItem: Text {
                                            text: parent.text
                                            color: textSecondary
                                            font.pixelSize: 11
                                            leftPadding: parent.indicator.width + 4
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                    }
                                    RadioButton {
                                        id: regMode
                                        text: "Reg"
                                        
                                        contentItem: Text {
                                            text: parent.text
                                            color: textSecondary
                                            font.pixelSize: 11
                                            leftPadding: parent.indicator.width + 4
                                            verticalAlignment: Text.AlignVCenter
                                        }
                                    }
                                }

                                // Goal Slider
                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 4

                                    RowLayout {
                                        Layout.fillWidth: true
                                        Text { text: "Goal:"; color: textSecondary; font.pixelSize: 12 }
                                        Item { Layout.fillWidth: true }
                                        TextField {
                                            id: goalInput
                                            Layout.preferredWidth: 80
                                            text: goalSlider.value.toFixed(0)
                                            color: textPrimary
                                            font.pixelSize: 12
                                            horizontalAlignment: Text.AlignRight
                                            
                                            background: Rectangle {
                                                radius: 4
                                                color: inputBgColor
                                                border.color: borderColor
                                            }
                                            
                                            onEditingFinished: {
                                                goalSlider.value = parseInt(text) || 2048
                                            }
                                        }
                                    }

                                    Slider {
                                        id: goalSlider
                                        Layout.fillWidth: true
                                        from: 0
                                        to: 4095
                                        value: 2048
                                        stepSize: 1

                                        background: Rectangle {
                                            x: goalSlider.leftPadding
                                            y: goalSlider.topPadding + goalSlider.availableHeight / 2 - height / 2
                                            width: goalSlider.availableWidth
                                            height: 6
                                            radius: 3
                                            color: inputBgColor

                                            Rectangle {
                                                width: goalSlider.visualPosition * parent.width
                                                height: parent.height
                                                radius: 3
                                                color: accentColor
                                            }
                                        }

                                        handle: Rectangle {
                                            x: goalSlider.leftPadding + goalSlider.visualPosition * (goalSlider.availableWidth - width)
                                            y: goalSlider.topPadding + goalSlider.availableHeight / 2 - height / 2
                                            width: 18
                                            height: 18
                                            radius: 9
                                            color: goalSlider.pressed ? Qt.lighter(accentColor, 1.2) : accentColor
                                            border.color: textPrimary
                                            border.width: 2
                                        }

                                        onMoved: {
                                            if (selectedServoId > 0) {
                                                servoGoal = value
                                                ddsManager.sendWritePos(selectedServoId, value, parseInt(speedInput.text) || 0, parseInt(accInput.text) || 0)
                                            }
                                        }
                                    }
                                }

                                // Speed / Acc / Time
                                GridLayout {
                                    Layout.fillWidth: true
                                    columns: 2
                                    rowSpacing: 8
                                    columnSpacing: 12

                                    Text { text: "Speed:"; color: textSecondary; font.pixelSize: 12 }
                                    TextField {
                                        id: speedInput
                                        Layout.fillWidth: true
                                        text: "0"
                                        color: textPrimary
                                        font.pixelSize: 12
                                        
                                        background: Rectangle {
                                            radius: 4
                                            color: inputBgColor
                                            border.color: borderColor
                                        }
                                    }

                                    Text { text: "Acc:"; color: textSecondary; font.pixelSize: 12 }
                                    TextField {
                                        id: accInput
                                        Layout.fillWidth: true
                                        text: "0"
                                        color: textPrimary
                                        font.pixelSize: 12
                                        
                                        background: Rectangle {
                                            radius: 4
                                            color: inputBgColor
                                            border.color: borderColor
                                        }
                                    }
                                }

                                // Set Button
                                Button {
                                    id: setBtn
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 40
                                    text: "📤 Set Position"
                                    enabled: selectedServoId > 0

                                    background: Rectangle {
                                        radius: 6
                                        color: setBtn.pressed ? Qt.darker(accentColor, 1.2) : 
                                               setBtn.hovered ? Qt.lighter(accentColor, 1.1) : accentColor
                                        opacity: setBtn.enabled ? 1.0 : 0.5
                                    }

                                    contentItem: Text {
                                        text: setBtn.text
                                        color: textPrimary
                                        font.pixelSize: 13
                                        font.weight: Font.Medium
                                        horizontalAlignment: Text.AlignHCenter
                                        verticalAlignment: Text.AlignVCenter
                                    }

                                    onClicked: {
                                        ddsManager.sendWritePos(
                                            selectedServoId,
                                            parseInt(goalInput.text) || 2048,
                                            parseInt(speedInput.text) || 0,
                                            parseInt(accInput.text) || 0
                                        )
                                    }
                                }

                                Rectangle { Layout.fillWidth: true; height: 1; color: borderColor }

                                // Torque Enable
                                RowLayout {
                                    Layout.fillWidth: true

                                    CheckBox {
                                        id: torqueCheck
                                        text: "Torque Enable"
                                        checked: torqueEnabled
                                        enabled: selectedServoId > 0

                                        contentItem: Text {
                                            text: parent.text
                                            color: textSecondary
                                            font.pixelSize: 12
                                            leftPadding: parent.indicator.width + 8
                                            verticalAlignment: Text.AlignVCenter
                                        }

                                        onCheckedChanged: {
                                            if (selectedServoId > 0) {
                                                ddsManager.sendEnableTorque(selectedServoId, checked)
                                                torqueEnabled = checked
                                            }
                                        }
                                    }
                                }

                                Item { Layout.fillHeight: true }
                            }
                        }

                        // --- Status Monitor ---
                        Rectangle {
                            Layout.fillWidth: true
                            Layout.fillHeight: true
                            radius: 8
                            color: cardColor
                            border.color: borderColor
                            border.width: 1

                            ColumnLayout {
                                anchors.fill: parent
                                anchors.margins: 12
                                spacing: 12

                                Text {
                                    text: "📊 Status Monitor" + (selectedServoId > 0 ? " (ID: " + selectedServoId + ")" : "")
                                    color: textPrimary
                                    font.pixelSize: 14
                                    font.weight: Font.Bold
                                }

                                Rectangle { Layout.fillWidth: true; height: 1; color: borderColor }

                                // Status Grid
                                GridLayout {
                                    Layout.fillWidth: true
                                    columns: 2
                                    rowSpacing: 16
                                    columnSpacing: 24

                                    // Position
                                    StatusItem { label: "Position"; value: servoPosition.toString(); unit: ""; valueColor: accentColor }
                                    StatusItem { label: "Goal"; value: servoGoal.toString(); unit: ""; valueColor: warningColor }
                                    
                                    // Load / Speed
                                    StatusItem { label: "Load"; value: servoLoad.toString(); unit: ""; valueColor: successColor }
                                    StatusItem { label: "Speed"; value: servoSpeed.toString(); unit: ""; valueColor: successColor }
                                    
                                    // Voltage / Current
                                    StatusItem { label: "Voltage"; value: servoVoltage.toFixed(1); unit: "V"; valueColor: warningColor }
                                    StatusItem { label: "Current"; value: servoCurrent.toString(); unit: "mA"; valueColor: warningColor }
                                    
                                    // Temperature / Moving
                                    StatusItem { label: "Temperature"; value: servoTemperature.toString(); unit: "°C"; valueColor: servoTemperature > 60 ? errorColor : successColor }
                                    StatusItem { label: "Moving"; value: servoMoving ? "Yes" : "No"; unit: ""; valueColor: servoMoving ? successColor : textSecondary }
                                }

                                Item { Layout.fillHeight: true }

                                // Message Log (compact)
                                Rectangle {
                                    Layout.fillWidth: true
                                    Layout.preferredHeight: 120
                                    radius: 6
                                    color: inputBgColor
                                    border.color: borderColor
                                    border.width: 1

                                    ListView {
                                        id: msgList
                                        anchors.fill: parent
                                        anchors.margins: 8
                                        model: ddsManager.messages
                                        clip: true
                                        spacing: 2

                                        delegate: Text {
                                            width: msgList.width
                                            text: modelData
                                            color: textSecondary
                                            font.pixelSize: 10
                                            font.family: "Consolas"
                                            elide: Text.ElideRight
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // ===== Programming Tab (Placeholder) =====
                    Rectangle {
                        color: cardColor
                        radius: 8
                        border.color: borderColor
                        border.width: 1

                        Text {
                            anchors.centerIn: parent
                            text: "⚙️ Programming Tab\n\nMemory Table & Edit\n(Coming Soon)"
                            color: textSecondary
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }
            }
        }

        // ========== Footer Status Bar ==========
        Rectangle {
            Layout.fillWidth: true
            height: 32
            radius: 6
            color: cardColor
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 12
                anchors.rightMargin: 12
                spacing: 16

                Text {
                    text: ddsManager.daemonConnected ? "● Daemon" : "○ Daemon"
                    color: ddsManager.daemonConnected ? successColor : errorColor
                    font.pixelSize: 11
                }

                Rectangle { width: 1; height: 14; color: borderColor }

                Text {
                    text: isConnected ? ("🔗 " + portCombo.currentText + " @ " + baudCombo.currentText) : "Disconnected"
                    color: isConnected ? successColor : textSecondary
                    font.pixelSize: 11
                }

                Rectangle { width: 1; height: 14; color: borderColor }

                Text {
                    text: selectedServoId > 0 ? ("Servo ID: " + selectedServoId) : "No servo selected"
                    color: selectedServoId > 0 ? accentColor : textSecondary
                    font.pixelSize: 11
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "Phase 2: Servo Control"
                    color: textSecondary
                    font.pixelSize: 11
                }
            }
        }
    }

    // ========== Status Item Component ==========
    component StatusItem: ColumnLayout {
        id: statusItemRoot
        property string label: ""
        property string value: ""
        property string unit: ""
        property color valueColor: textPrimary

        spacing: 4

        Text {
            text: statusItemRoot.label
            color: textSecondary
            font.pixelSize: 11
        }
        RowLayout {
            spacing: 4
            Text {
                text: statusItemRoot.value
                color: statusItemRoot.valueColor
                font.pixelSize: 24
                font.weight: Font.Bold
            }
            Text {
                text: statusItemRoot.unit
                color: textSecondary
                font.pixelSize: 12
                visible: statusItemRoot.unit !== ""
            }
        }
    }

    // ========== Timers ==========
    Timer {
        id: scanTimer
        interval: 2000
        onTriggered: {
            isSearching = false
            // 임시: 테스트용 더미 데이터 (실제로는 DDS feedback에서 받음)
            foundServos = [
                { id: 1, model: "ST3215" }
            ]
        }
    }

    Timer {
        id: readStateTimer
        interval: 100
        repeat: true
        onTriggered: {
            if (selectedServoId > 0 && isConnected) {
                ddsManager.sendReadState(selectedServoId)
            }
        }
    }
}
