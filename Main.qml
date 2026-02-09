/*
 * Main.qml - FT SCServo Qt6 DDS GUI
 * Precisely matched to the provided .ui file coordinates and structure.
 * UI Version: MainWindow (937x706)
 */

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    id: window
    width: 937
    height: 706
    visible: true
    title: "Feetech Servo Tool"

    // ========== DESIGN SYSTEM ==========
    readonly property color cBg: "#0c0c0e"
    readonly property color cPanel: "#18181b"
    readonly property color cBorder: "#27272a"
    readonly property color cAccent: "#3b82f6"
    readonly property color cText: "#fafafa"
    readonly property color cSub: "#a1a1aa"
    readonly property color cHighlight: "#2563eb"
    readonly property color cEdit: "#09090b"

    background: Rectangle { color: cBg }

    // ========== APP STATE ==========
    property bool isConnected: false
    property bool isSearching: false
    property int selectedId: -1
    property var servoList: []
    
    property int stPos: 0
    property int stGoal: 0
    property int stSpeed: 0
    property int stLoad: 0
    property real stVolt: 0.0
    property int stTemp: 0
    property int stCurr: 0
    property int stMove: 0
    property bool torqueOn: true

    // ========== REUSABLE GROUPBOX ==========
    component GroupBox : Rectangle {
        property string title: ""
        color: cPanel; radius: 4; border.color: cBorder; border.width: 1
        Text {
            text: parent.title; color: cAccent; font.pixelSize: 11; font.bold: true
            x: 12; y: 8
        }
    }

    // ========== CENTRAL WIDGET AREA ==========
    Item {
        id: centralWidget
        anchors.fill: parent

        // --- Com Settings (x:10, y:10, w:171, h:191) ---
        GroupBox {
            title: "Com Settings"
            x: 10; y: 10; width: 171; height: 191
            
            ColumnLayout {
                x: 5; y: 30; width: 161; height: 161
                GridLayout {
                    columns: 2; rowSpacing: 8; columnSpacing: 5
                    Text { text: "Com"; color: cSub; font.pixelSize: 10 }
                    ComboBox { id: pCom; Layout.fillWidth: true; model: ["COM1", "COM3", "COM6", "COM7"]; currentIndex: 2; enabled: !isConnected; font.pixelSize: 10; implicitHeight: 22 }
                    Text { text: "BaudR"; color: cSub; font.pixelSize: 10 }
                    ComboBox { id: bCom; Layout.fillWidth: true; model: ["1000000", "500000", "115200"]; currentIndex: 0; enabled: !isConnected; font.pixelSize: 10; implicitHeight: 22 }
                    Text { text: "DParity"; color: cSub; font.pixelSize: 10 }
                    ComboBox { Layout.fillWidth: true; model: ["NONE", "ODD", "EVEN"]; font.pixelSize: 10; implicitHeight: 22 }
                    Text { text: "TimeOut"; color: cSub; font.pixelSize: 10 }
                    TextField { id: tOut; Layout.fillWidth: true; text: "50"; enabled: !isConnected; font.pixelSize: 10; implicitHeight: 22; background: Rectangle { color: cEdit; border.color: cBorder } }
                }
                Item { Layout.fillHeight: true }
                Button {
                    Layout.alignment: Qt.AlignRight
                    text: isConnected ? "Close" : "Open"; implicitHeight: 26; font.pixelSize: 11
                    onClicked: {
                        if (isConnected) { ddsManager.sendDisconnect(); isConnected = false; }
                        else { ddsManager.sendConnect(pCom.currentText, parseInt(bCom.currentText)); isConnected = true; }
                    }
                }
            }
        }

        // --- Servo List (x:10, y:210, w:171, h:471) ---
        GroupBox {
            title: "Servo List"
            x: 10; y: 210; width: 171; height: 471
            
            ColumnLayout {
                x: 5; y: 30; width: 161; height: 431; spacing: 8
                Button {
                    text: "Search"; Layout.alignment: Qt.AlignRight; enabled: isConnected; implicitHeight: 22; font.pixelSize: 10
                    onClicked: { isSearching = true; ddsManager.sendScan(); scanTimer.start(); }
                }
                TextField {
                    Layout.fillWidth: true; text: isSearching ? "Scanning..." : "-"; readOnly: true; font.pixelSize: 10; implicitHeight: 22
                    background: Rectangle { color: cEdit; border.color: cBorder }
                }
                Rectangle {
                    Layout.fillWidth: true; Layout.fillHeight: true; color: "#000"; border.color: cBorder; clip: true
                    ListView {
                        id: sView; anchors.fill: parent; model: servoList
                        delegate: Rectangle {
                            width: sView.width; height: 24; color: selectedId === modelData.id ? cHighlight : "transparent"
                            Text { text: "ID: " + modelData.id; color: "#fff"; anchors.centerIn: parent; font.pixelSize: 11 }
                            MouseArea { anchors.fill: parent; onClicked: { selectedId = modelData.id; readStateTimer.start(); } }
                        }
                    }
                }
            }
        }

        // --- Tab Widget (x:190, y:10, w:741, h:671) ---
        Rectangle {
            x: 190; y: 10; width: 741; height: 671; color: "transparent"
            
            TabBar {
                id: bar; width: parent.width; height: 30
                TabButton { text: "Debug"; font.pixelSize: 11; width: 100 }
                TabButton { text: "Programming"; font.pixelSize: 11; width: 120 }
            }

            StackLayout {
                id: tabs; anchors.top: bar.bottom; anchors.bottom: parent.bottom; width: parent.width; currentIndex: bar.currentIndex
                
                // Debug Tab
                Item {
                    // Graph (x:10, y:10, w:601, h:351)
                    Rectangle {
                        x: 10; y: 10; width: 601; height: 351; color: "#050507"; border.color: cBorder
                        Canvas {
                            anchors.fill: parent; anchors.margins: 15
                            onPaint: {
                                var ctx = getContext("2d"); ctx.clearRect(0,0,width,height); ctx.strokeStyle="#1a1a1e"; ctx.lineWidth=1;
                                for(var i=0; i<=20; i++){ ctx.beginPath(); ctx.moveTo(i*width/20,0); ctx.lineTo(i*width/20,height); ctx.stroke(); }
                                for(var j=0; j<=10; j++){ ctx.beginPath(); ctx.moveTo(0,j*height/10); ctx.lineTo(width,j*height/10); ctx.stroke(); }
                            }
                        }
                    }

                    // Servo Control (x:10, y:365, w:411, h:161)
                    GroupBox {
                        title: "Servo Control"
                        x: 10; y: 365; width: 411; height: 161
                        ColumnLayout {
                            x: 10; y: 30; width: 391; height: 121; spacing: 5
                            RowLayout {
                                RadioButton { text: "Write"; checked: true; font.pixelSize: 9 }
                                RadioButton { text: "Sync Write"; font.pixelSize: 9 }
                                RadioButton { text: "Reg Write"; font.pixelSize: 9 }
                                CheckBox { text: "Torque Enable"; font.pixelSize: 9; checked: torqueOn; onCheckedChanged: if(selectedId>0) ddsManager.sendEnableTorque(selectedId, checked) }
                            }
                            Slider { id: gSli; Layout.fillWidth: true; from: 0; to: 4095; value: 2047 }
                            GridLayout {
                                columns: 5; rowSpacing: 8; columnSpacing: 10
                                Text { text: "Acc"; color: cSub; font.pixelSize: 9 }
                                TextField { id: aIn; text: "0"; Layout.preferredWidth: 50; implicitHeight: 20; background: Rectangle { color: cEdit; border.color: cBorder } }
                                Text { text: "Goal"; color: cSub; font.pixelSize: 9 }
                                TextField { id: gIn; text: Math.round(gSli.value).toString(); Layout.preferredWidth: 60; implicitHeight: 20; background: Rectangle { color: cEdit; border.color: cBorder } }
                                Button { text: "Action"; implicitWidth: 60; implicitHeight: 22 }
                                Text { text: "Speed"; color: cSub; font.pixelSize: 9 }
                                TextField { id: sIn; text: "100"; Layout.preferredWidth: 50; implicitHeight: 20; background: Rectangle { color: cEdit; border.color: cBorder } }
                                Text { text: "Time"; color: cSub; font.pixelSize: 9 }
                                TextField { text: "0"; Layout.preferredWidth: 60; implicitHeight: 20; background: Rectangle { color: cEdit; border.color: cBorder } }
                                Button { text: "Set"; highlighted: true; implicitWidth: 60; implicitHeight: 22; onClicked: if(selectedId>0) ddsManager.sendWritePos(selectedId, parseInt(gIn.text), parseInt(sIn.text), parseInt(aIn.text)) }
                            }
                        }
                    }

                    // Auto debug (x:10, y:530, w:411, h:101)
                    GroupBox {
                        title: "Auto debug"
                        x: 10; y: 530; width: 411; height: 101
                        GridLayout {
                            x: 10; y: 25; width: 391; height: 70; columns: 6; columnSpacing: 10
                            Text { text: "Start"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "0"; Layout.preferredWidth: 50; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            Text { text: "Delay(Sweep)"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "2500"; Layout.preferredWidth: 50; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            Item { Layout.fillWidth: true }
                            Button { text: "Sweep"; implicitWidth: 60; implicitHeight: 20; font.pixelSize: 9 }
                            Text { text: "End"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "4095"; Layout.preferredWidth: 50; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            Text { text: "Step:Delay"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "10"; Layout.preferredWidth: 50; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            Item { Layout.fillWidth: true }
                            Button { text: "Step"; implicitWidth: 60; implicitHeight: 20; font.pixelSize: 9 }
                        }
                    }

                    // Servo Feedback (x:430, y:365, w:301, h:161)
                    GroupBox {
                        title: "Servo Feedback"
                        x: 430; y: 365; width: 301; height: 161
                        GridLayout {
                            x: 10; y: 25; width: 281; height: 130; columns: 4; rowSpacing: 2
                            Text { text: "Voltage:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: stVolt.toFixed(1) + "V"; color: "#fff"; font.pixelSize: 9; font.bold: true }
                            Text { text: "Torque:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stLoad); color: "#fff"; font.pixelSize: 9; font.bold: true }
                            Text { text: "Current:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stCurr); color: "#fff"; font.pixelSize: 9 }
                            Text { text: "Speed:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stSpeed); color: "#fff"; font.pixelSize: 9 }
                            Text { text: "Temperature:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stTemp); color: "#fff"; font.pixelSize: 9 }
                            Text { text: "Position:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stPos); color: cAccent; font.pixelSize: 10; font.bold: true }
                            Text { text: "Moving:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stMove); color: "#fff"; font.pixelSize: 9 }
                            Text { text: "Goal:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: String(stGoal); color: "#fff"; font.pixelSize: 9 }
                            Text { text: "State:"; color: cSub; font.pixelSize: 9; Layout.alignment: Qt.AlignRight }
                            Text { text: "-"; color: "#fff"; font.pixelSize: 9; Layout.columnSpan: 3 }
                        }
                    }

                    // Data analysis (x:430, y:530, w:301, h:101)
                    GroupBox {
                        title: "Data analysis"
                        x: 430; y: 530; width: 301; height: 101
                        GridLayout {
                            x: 10; y: 25; width: 281; height: 70; columns: 4; columnSpacing: 8
                            Text { text: "time(s)"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "30"; Layout.preferredWidth: 40; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            Item { Layout.fillWidth: true }
                            Button { text: "Export"; implicitWidth: 50; implicitHeight: 20; font.pixelSize: 9 }
                            Text { text: "file:rows"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "record.csv"; Layout.fillWidth: true; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            TextField { text: "0"; Layout.preferredWidth: 40; readOnly: true; font.pixelSize: 9; implicitHeight: 18; background: Rectangle { color: "#111"; border.color: cBorder } }
                            Button { text: "Empty"; implicitWidth: 50; implicitHeight: 20; font.pixelSize: 9 }
                        }
                    }

                    // Checkboxes/Settings (x:620, y:60, w:111, h:304)
                    ColumnLayout {
                        x: 620; y: 60; width: 111; height: 304; spacing: 2
                        Repeater {
                            model: ["Position", "Torque", "Speed", "Current", "Temperature", "Voltage"]
                            CheckBox { text: modelData; font.pixelSize: 9; checked: index < 3; padding: 0 }
                        }
                        Text { text: "Horizontal"; color: cSub; font.pixelSize: 9 }
                        Slider { Layout.fillWidth: true; height: 16 }
                        Text { text: "Zoom X"; color: cSub; font.pixelSize: 9 }
                        Slider { Layout.fillWidth: true; height: 16 }
                        GridLayout {
                            columns: 2; columnSpacing: 5
                            Text { text: "Up"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "0"; Layout.fillWidth: true; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                            Text { text: "Down"; color: cSub; font.pixelSize: 9 }
                            TextField { text: "0"; Layout.fillWidth: true; implicitHeight: 18; font.pixelSize: 9; background: Rectangle { color: cEdit; border.color: cBorder } }
                        }
                        Item { Layout.fillHeight: true }
                    }
                }

                // Programming Tab
                Rectangle { color: cPanel; Text { text: "Memory Table Interface"; anchors.centerIn: parent; color: cSub } }
            }
        }
    }

    // ========== Logic ==========
    Connections {
        target: ddsManager
        ignoreUnknownSignals: true
        function onScanResultReceived(ids) {
            isSearching = false
            var n = []
            for(var i=0; i<ids.length; i++) n.push({id: ids[i]})
            servoList = n
        }
        function onServoStateReceived(id, pos, spd, load, vlt, temp, curr, move) {
            if (id === selectedId) {
                stPos = pos; stSpeed = spd; stLoad = load; stVolt = vlt;
                stTemp = temp; stCurr = curr; stMove = move;
                stGoal = Math.round(gSli.value)
            }
        }
    }

    Timer { id: scanTimer; interval: 5000; onTriggered: isSearching = false }
    Timer { id: readStateTimer; interval: 100; repeat: true; onTriggered: if(selectedId > 0 && isConnected) ddsManager.sendReadState(selectedId) }
}
