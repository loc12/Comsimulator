import QtQuick 2.0

Rectangle{
    id: logViewArea
    color: "#dfe4ea"
    border.color: "gray"
    Text{
        id: labelLogView
        anchors.top: parent.top
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 6
        font.bold: true
        font.pixelSize: 16
        text: qsTr("Recent Log:")
    }

    Rectangle{
        id: header_time
        width: parent.width/2
        height: 30
        anchors.top: labelLogView.bottom
        anchors.topMargin: 3
        anchors.left: parent.left
        anchors.leftMargin: 0
        color: "lightblue"
        border.color: "gray"
        clip: true
        Text {
            text: qsTr("Time")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    Rectangle{
        id: header_content
        width: parent.width/2
        height: 30
        anchors.top: labelLogView.bottom
        anchors.topMargin: 3
        anchors.right: parent.right
        anchors.rightMargin: 0
        color: "lightblue"
        border.color: "gray"
        clip: true
        Text {
            text: qsTr("Content Log")
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
        }
    }
    ListView{
        id: list_logView
        width: parent.width
        height: parent.height - header_content.height - labelLogView.height
        anchors.top: header_content.bottom
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        snapMode: ListView.SnapToItem
        focus: true
        clip: true
        model: logModel
        delegate: Rectangle{
            id: recDelegate
            width: logViewArea.width
            height: 30
            Rectangle{
                id: txt_time
                width: parent.width/2
                height: parent.height
                anchors.left: parent.left
                anchors.verticalCenter: parent.verticalCenter
                border.color: "gray"
                Text{
                    anchors.left: parent.left
                    anchors.leftMargin: 3
                    anchors.verticalCenter: parent.verticalCenter
                    text: datetime
                    color: colorlog
                }
            }
            Rectangle{
                id: txt_content
                width: parent.width/2
                height: parent.height
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                border.color: "gray"
                Text{
                    anchors.left: parent.left
                    anchors.leftMargin: 3
                    anchors.verticalCenter: parent.verticalCenter
                    text: content
                    color: colorlog
                }
            }
        }
    }
}
