import QtQuick 2.0
import "./Component"
import Enum 1.0

Rectangle{
    id: commsettingArea
    color: "#dfe4ea"
    border.color: "gray"
    signal connect()
    signal disconnect()
    signal updateComPortSetting(int portNo, int baudRate, int dataBit, int parity)
    property int currentPortNoIndex: 0
    property int currentBaudRateIndex: 0
    property int currentDataBitsIndex: 0
    property int currentParityIndex: 0
    property int currentStopBit: 0
    property bool isOpenedCom: false
    Text{
        id: labelSetting
        text: qsTr("Serial Port Com Setting:")
        font.bold: true
        font.pixelSize: 16
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.top: parent.top
        anchors.topMargin: 3
    }

    // Setup PortNo
    ComboBox{
        id: cbPortNo
        elements: ["COM1","COM2","COM3","COM4"]
        anchors.left: txtPortNo.right
        anchors.leftMargin: 50
        anchors.top: labelSetting.bottom
        anchors.topMargin: 8
        currentItem: currentPortNoIndex
    }
    Text {
        id: txtPortNo
        text: qsTr("PortNo:")
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.verticalCenter: cbPortNo.verticalCenter
    }
    // Setup BaudRate
    ComboBox{
        id: cbBaudRate
        elements: ["4800","9600"]
        anchors.horizontalCenter: cbPortNo.horizontalCenter
        anchors.top: cbPortNo.bottom
        anchors.topMargin: 5
        currentItem: currentBaudRateIndex
    }
    Text{
        id: txtBaudRate
        text: qsTr("BaudRate:")
        anchors.left: txtPortNo.left
        anchors.leftMargin: 0
        anchors.verticalCenter: cbBaudRate.verticalCenter
    }

    // Setup Data Bits
    ComboBox{
        id: cbDataBits
        elements: ["7","8"]
        anchors.horizontalCenter: cbPortNo.horizontalCenter
        anchors.top: cbBaudRate.bottom
        anchors.topMargin: 5
        currentItem: currentDataBitsIndex
    }
    Text{
        id: txtDataBits
        text: qsTr("DataBits:")
        anchors.left: txtPortNo.left
        anchors.leftMargin: 0
        anchors.verticalCenter: cbDataBits.verticalCenter
    }
    // Parity
    ComboBox{
        id: cbParity
        elements: ["None","Even","Odd"]
        anchors.horizontalCenter: cbPortNo.horizontalCenter
        anchors.top: cbDataBits.bottom
        anchors.topMargin: 5
        currentItem: currentParityIndex
    }
    Text{
        id: txtParity
        text: qsTr("Parity:")
        anchors.left: txtPortNo.left
        anchors.leftMargin: 0
        anchors.verticalCenter: cbParity.verticalCenter
    }

    // Connect button
    Button{
        id: btnConnect
        width: 85
        height: 30
        contentActive: "Open"
        contentInactive: "Close"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 15
        anchors.left: parent.left
        anchors.leftMargin: 10
        colorOn: "green"
        colorOff: "red"
        onChangeStatus: {
            if(btnConnect.isActive === true){
                connect();
            }
            else {
                disconnect();
            }
        }
    }
    // Handle the signal from qml
    // Signal from Combobox PortNo
    Connections{
        id: connection1
        target: cbPortNo
        onOpenCombobox: {
            cbPortNo.z = 2
            console.log("Disable another mouse area!!!")
            cbBaudRate.isEnable = false
            cbDataBits.isEnable = false
            cbParity.isEnable = false
        }
        onCloseExpand: {
            console.log("Close the expand combobox")
            resetStatus();
        }
    }
    // Signal from ComboBox BaudRate
    Connections{
        target: cbBaudRate
        onOpenCombobox: {
            cbBaudRate.z = 2
            console.log("Disable another mouse area!!!")
            cbPortNo.isEnable       = false
            cbDataBits.isEnable     = false
            cbParity.isEnable       = false
        }
        onCloseExpand: {
            console.log("Close the expand combobox")
            resetStatus();
        }
    }
    // Signal from ComboBox Data Bits
    Connections{
        target: cbDataBits
        onOpenCombobox: {
            cbDataBits.z = 2
            console.log("Disable another mouse area!!!")
            cbPortNo.isEnable       = false
            cbBaudRate.isEnable     = false
            cbParity.isEnable       = false
        }
        onCloseExpand: {
            console.log("Close the expand combobox")
            resetStatus();
        }
    }
    // Signal from ComboBox Parity
    Connections{
        target: cbParity
        onOpenCombobox: {
            cbParity.z = 2
            console.log("Disable another mouse area!!!")
            cbPortNo.isEnable       = false
            cbBaudRate.isEnable     = false
            cbDataBits.isEnable     = false
        }
        onCloseExpand: {
            console.log("Close the expand combobox")
            resetStatus();
        }
    }
    // Define javascript function
    // Reset the status
    function resetStatus(){
        // Reset MouseArea
        if(isOpenedCom){
            disableSettingComPort();
        }
        else {
            enableSettingComPort();
            var portNo      = [Enum.E_COM1, Enum.E_COM2, Enum.E_COM3, Enum.E_COM4];
            var baudRate    = [Enum.E_BAUD_4800, Enum.E_BAUD_9600];
            var dataBit     = [Enum.E_DATA_SIZE_7, Enum.E_DATA_SIZE_8];
            var parity      = [Enum.E_PARITY_NONE, Enum.E_PARITY_EVEN, Enum.E_PARITY_ODD];
            cbPortNo.z      = 1;
            cbBaudRate.z    = 1;
            cbDataBits.z    = 1;
            cbParity.z      = 1;
            // Get the current setting
            currentPortNoIndex      = cbPortNo.currentItem
            currentBaudRateIndex    = cbBaudRate.currentItem
            currentDataBitsIndex    = cbDataBits.currentItem
            currentParityIndex      = cbParity.currentItem

            updateComPortSetting(portNo[currentPortNoIndex], baudRate[currentBaudRateIndex], dataBit[currentDataBitsIndex], parity[currentParityIndex])
        }
    }
    function disableSettingComPort(){
        cbPortNo.isEnable       = false;
        cbBaudRate.isEnable     = false;
        cbDataBits.isEnable     = false;
        cbParity.isEnable       = false;
    }
    function enableSettingComPort(){
        cbPortNo.isEnable       = true;
        cbBaudRate.isEnable     = true;
        cbDataBits.isEnable     = true;
        cbParity.isEnable       = true;
    }

    Connections {
        target: portcom
        onOpenComPortNG: {
            btnConnect.isActive = false;
            enableSettingComPort();
        }
        onOpenComPortOK: {      // Do not allow to change the Setting of Port Com
            disableSettingComPort();
        }
        onCloseComPortOK:{
            enableSettingComPort();
        }
    }
}
