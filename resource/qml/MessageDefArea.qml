import QtQuick 2.0

Rectangle{
    id: messageDefArea
    border.color: "gray"
    color: "#dfe4ea"
    signal sendMessage(string msg)
    property bool isEnable: true
//    property string highlightColor: isEnable ? "green" : "#dfe4ea"
    Text{
        id: labelMessageDef
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 6
        font.bold: true
        font.pixelSize: 16
        text: qsTr("Define Sending Message:")
    }
    ListView{
        id: listviewMessagesDef
        width: parent.width
        height: parent.height - labelMessageDef.height - 20
        anchors.top: labelMessageDef.bottom
        anchors.topMargin: 10
        anchors.left: parent.left
        anchors.leftMargin: 5
        spacing: 1
        model: sendMessages
        delegate: messageDelegate
        clip: true
        snapMode: ListView.SnapOneItem
        highlight: highlight
    }
    Component{
        id: messageDelegate
        Rectangle{
            id: recMsgDef
            width: messageDefArea.width - 10
            height: 30
            color: "#dfe4ea"
            radius: 5
            Text {
                id: txtMessageName
                text: name
                anchors.left: parent.left
                anchors.leftMargin: 6
                anchors.verticalCenter: parent.verticalCenter
            }
            border.color: "gray"
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    listviewMessagesDef.currentIndex = index
                }
                onDoubleClicked: {
                    sendMessage(content);
                }
            }
        }
    }
    Component {
         id: highlight
         Rectangle {
             width: listviewMessagesDef.width - 10
             height: 30
             color: listviewMessagesDef.isCurrentItem ? "black" : "green";
             radius: 5
             opacity: 0.4
             z: 2

             y: listviewMessagesDef.currentItem.y
             Behavior on y {
                 SpringAnimation {
                     spring: 3
                     damping: 0.2
                 }
             }
         }
     }
}
