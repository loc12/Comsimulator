import QtQuick 2.0

Rectangle{
    id: button
    property string colorOn: "green"
    property string colorOff: "gray"
    property string contentActive
    property string contentInactive
    property int radiusNum: 7
    property bool isActive: false
    signal changeStatus()
    radius: radiusNum
    color: isActive ? colorOn : colorOff
    Rectangle{
        id: subRec
        anchors.fill: parent
        radius: radiusNum
        color: "transparent"
        opacity: 0.6
    }

    Text{
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        text: isActive ? contentActive : contentInactive
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            isActive = !isActive;
            changeStatus();
        }
        onPressed: {
            subRec.color = "#CCCCFF"
        }
        onReleased: {
            subRec.color = "transparent"
        }
        onCanceled: {
            subRec.color = "transparent"
        }
    }
}
