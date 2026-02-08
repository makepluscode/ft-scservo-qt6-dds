/*
 * Main.qml - FT SCServo Qt6 GUI
 * Phase 1-A: DDS Ping-Pong 테스트 UI
 * 해상도: 1280 x 720
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: mainWindow
    width: 1280
    height: 720
    visible: true
    title: "FT SCServo Qt6 - DDS Test"
    color: "#0f0f0f"

    // 다크 테마 색상
    readonly property color bgColor: "#0f0f0f"
    readonly property color cardColor: "#1a1a1a"
    readonly property color cardHoverColor: "#252525"
    readonly property color accentColor: "#3b82f6"
    readonly property color successColor: "#22c55e"
    readonly property color errorColor: "#ef4444"
    readonly property color textPrimary: "#ffffff"
    readonly property color textSecondary: "#a0a0a0"
    readonly property color borderColor: "#333333"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 16

        // ========== Header ==========
        Rectangle {
            Layout.fillWidth: true
            height: 60
            radius: 12
            color: cardColor
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 16

                // 연결 상태 표시등
                Rectangle {
                    width: 14
                    height: 14
                    radius: 7
                    color: ddsManager.daemonConnected ? successColor : errorColor

                    SequentialAnimation on opacity {
                        running: !ddsManager.daemonConnected
                        loops: Animation.Infinite
                        NumberAnimation { to: 0.4; duration: 500 }
                        NumberAnimation { to: 1.0; duration: 500 }
                    }
                }

                Text {
                    text: ddsManager.status
                    color: textPrimary
                    font.pixelSize: 16
                    font.weight: Font.Medium
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "FT SCServo Qt6"
                    color: textSecondary
                    font.pixelSize: 14
                }
            }
        }

        // ========== Main Content ==========
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            spacing: 16

            // ===== Left Panel: Controls =====
            Rectangle {
                Layout.preferredWidth: 320
                Layout.fillHeight: true
                radius: 12
                color: cardColor
                border.color: borderColor
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 20

                    // Title
                    Text {
                        text: "DDS Communication Test"
                        color: textPrimary
                        font.pixelSize: 18
                        font.weight: Font.Bold
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: borderColor
                    }

                    // Ping/Pong 카운터
                    GridLayout {
                        Layout.fillWidth: true
                        columns: 2
                        rowSpacing: 12
                        columnSpacing: 16

                        Text {
                            text: "Ping Sent:"
                            color: textSecondary
                            font.pixelSize: 14
                        }
                        Text {
                            text: ddsManager.pingCount
                            color: accentColor
                            font.pixelSize: 24
                            font.weight: Font.Bold
                        }

                        Text {
                            text: "Pong Received:"
                            color: textSecondary
                            font.pixelSize: 14
                        }
                        Text {
                            text: ddsManager.pongCount
                            color: successColor
                            font.pixelSize: 24
                            font.weight: Font.Bold
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: borderColor
                    }

                    // Ping 버튼
                    Button {
                        id: pingButton
                        Layout.fillWidth: true
                        Layout.preferredHeight: 56
                        text: "🏓 Send Ping"
                        enabled: ddsManager.daemonConnected

                        background: Rectangle {
                            radius: 10
                            color: pingButton.pressed ? Qt.darker(accentColor, 1.2) :
                                   pingButton.hovered ? Qt.lighter(accentColor, 1.1) : accentColor
                            opacity: pingButton.enabled ? 1.0 : 0.5

                            Behavior on color { ColorAnimation { duration: 150 } }
                        }

                        contentItem: Text {
                            text: pingButton.text
                            color: textPrimary
                            font.pixelSize: 16
                            font.weight: Font.Medium
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        onClicked: ddsManager.sendPing()
                    }

                    // Clear 버튼
                    Button {
                        id: clearButton
                        Layout.fillWidth: true
                        Layout.preferredHeight: 44
                        text: "🗑️ Clear Messages"

                        background: Rectangle {
                            radius: 8
                            color: clearButton.pressed ? "#333" :
                                   clearButton.hovered ? "#2a2a2a" : "transparent"
                            border.color: borderColor
                            border.width: 1

                            Behavior on color { ColorAnimation { duration: 150 } }
                        }

                        contentItem: Text {
                            text: clearButton.text
                            color: textSecondary
                            font.pixelSize: 14
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                        }

                        onClicked: ddsManager.clearMessages()
                    }

                    Item { Layout.fillHeight: true }

                    // 도움말
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: infoColumn.height + 24
                        radius: 8
                        color: "#1e293b"
                        border.color: "#334155"
                        border.width: 1

                        ColumnLayout {
                            id: infoColumn
                            anchors.left: parent.left
                            anchors.right: parent.right
                            anchors.top: parent.top
                            anchors.margins: 12
                            spacing: 8

                            Text {
                                text: "ℹ️ Instructions"
                                color: "#93c5fd"
                                font.pixelSize: 13
                                font.weight: Font.Medium
                            }

                            Text {
                                Layout.fillWidth: true
                                text: "1. Run ServoDaemon.exe first\n2. Wait for connection\n3. Click 'Send Ping' to test"
                                color: "#cbd5e1"
                                font.pixelSize: 12
                                wrapMode: Text.Wrap
                                lineHeight: 1.4
                            }
                        }
                    }
                }
            }

            // ===== Right Panel: Messages =====
            Rectangle {
                Layout.fillWidth: true
                Layout.fillHeight: true
                radius: 12
                color: cardColor
                border.color: borderColor
                border.width: 1

                ColumnLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    spacing: 12

                    RowLayout {
                        Layout.fillWidth: true

                        Text {
                            text: "📨 Message Log"
                            color: textPrimary
                            font.pixelSize: 18
                            font.weight: Font.Bold
                        }

                        Item { Layout.fillWidth: true }

                        Text {
                            text: ddsManager.messages.length + " messages"
                            color: textSecondary
                            font.pixelSize: 12
                        }
                    }

                    Rectangle {
                        Layout.fillWidth: true
                        height: 1
                        color: borderColor
                    }

                    ListView {
                        id: messageList
                        Layout.fillWidth: true
                        Layout.fillHeight: true
                        model: ddsManager.messages
                        clip: true
                        spacing: 6

                        ScrollBar.vertical: ScrollBar {
                            active: true
                            policy: ScrollBar.AsNeeded
                        }

                        delegate: Rectangle {
                            width: messageList.width - 12
                            height: msgText.height + 16
                            radius: 6
                            color: index % 2 === 0 ? "#1f1f1f" : "#242424"

                            Text {
                                id: msgText
                                anchors.left: parent.left
                                anchors.right: parent.right
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.margins: 12
                                text: modelData
                                color: {
                                    if (modelData.includes("PONG")) return successColor
                                    if (modelData.includes("PING")) return accentColor
                                    if (modelData.includes("Error") || modelData.includes("failed")) return errorColor
                                    return textSecondary
                                }
                                font.pixelSize: 13
                                font.family: "Consolas"
                                wrapMode: Text.Wrap
                            }
                        }

                        // 빈 상태 표시
                        Text {
                            anchors.centerIn: parent
                            visible: messageList.count === 0
                            text: "No messages yet.\nClick 'Send Ping' to start testing."
                            color: textSecondary
                            font.pixelSize: 14
                            horizontalAlignment: Text.AlignHCenter
                            opacity: 0.6
                        }
                    }
                }
            }
        }

        // ========== Footer Status Bar ==========
        Rectangle {
            Layout.fillWidth: true
            height: 36
            radius: 8
            color: cardColor
            border.color: borderColor
            border.width: 1

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 16
                anchors.rightMargin: 16
                spacing: 24

                Text {
                    text: ddsManager.daemonConnected ? "● Daemon Connected" : "○ Daemon Disconnected"
                    color: ddsManager.daemonConnected ? successColor : errorColor
                    font.pixelSize: 12
                }

                Rectangle { width: 1; height: 16; color: borderColor }

                Text {
                    text: "Domain: 0"
                    color: textSecondary
                    font.pixelSize: 12
                }

                Rectangle { width: 1; height: 16; color: borderColor }

                Text {
                    text: "Topics: ServoCommand, ServoFeedback"
                    color: textSecondary
                    font.pixelSize: 12
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "Phase 1-A: DDS Test"
                    color: textSecondary
                    font.pixelSize: 12
                }
            }
        }
    }
}
