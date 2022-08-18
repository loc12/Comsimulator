import QtQuick 2.2
import QtQuick.Window 2.2

Window {
    id: root
    width: WIDTH_SCREEN
    height: HEIGHT_SCREEN
    minimumWidth: MIN_WIDTH_SCREEN
    minimumHeight: MIN_HEIGHT_SCREEN
    // define the signal from qml to c++
    signal connectCom();
    signal disconnectCom();
    signal sendMessageToCpp(string msg)
    visible: true
    title: qsTr("Comm Simulator")
    color: "#dfe4ea"
    Loader{
        id: logViewArea
        sourceComponent: logViewLoader
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
    }
    Component{
        id: logViewLoader
        LogViewArea{
            width: root.width - 250 - 1
            height: root.height
            radius: 5
        }
    }

    Loader{
        id: messageDefArea
        sourceComponent: messageDefLoader
        anchors.right: parent.right
        anchors.top: parent.top
    }

    Component{
        id: messageDefLoader
        MessageDefArea{
            width: 250
            height: root.height - 250 - 1
            radius: 5
        }
    }
    Component{
        id: ackMessageLoader
        AckMessageArea{
            width: 250
            height: root.height - 250 - 1
            radius: 5
        }
    }

    Loader{
        id: settingArea
        sourceComponent: commSettingLoader
        anchors.right: parent.right
        anchors.bottom: parent.bottom
    }
    Component{
        id: commSettingLoader
        CommSettingArea{
            id: comSettingArea
            currentPortNoIndex: 0
            currentBaudRateIndex: 1
            currentDataBitsIndex: 1
            currentParityIndex: 0
            currentStopBit: 0
            width: 250
            height: 250
            radius: 5
        }
    }

    // Handle the signal from QML
    Connections{
        target: settingArea.item
        onConnect: {
            connectCom();
        }
        onDisconnect: {
            disconnectCom();
        }
        onUpdateComPortSetting: {
            simulator.settingPortCom(portNo, baudRate, dataBit, parity);
        }
    }
    Connections{
        target: messageDefArea.item
        onSendMessage: {
            sendMessageToCpp(msg)
            messageDefArea.sourceComponent = messageDefLoader;
        }
    }
    Connections {
        target: simulator
        onShowAckMessages: {
            messageDefArea.sourceComponent = ackMessageLoader;
        }
    }
}
