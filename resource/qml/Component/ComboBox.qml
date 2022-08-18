import QtQuick 2.0

Rectangle{
    id: id_combobox
    property var elements: ["combobox1","combobox2","combobox3"]
    property int radiusNum: 3
    property bool isExpandDown: false
    property int currentItem: 0
    property bool isEnable: true
    color: isEnable ? "#F5FFFA" : "gray"
    border.color: "gray"
    radius: radiusNum
    width: 120
    height: 30
    // define the signal
    signal closeExpand()
    signal openCombobox()
    Image {
        id: img_expand
        width: 20
        height: 20
        visible: (elements.length > 1) ? true : false
        source: "qrc:/2x/expand_more_black_24dp.png"
        anchors.right: parent.right
        anchors.rightMargin: 3
        anchors.verticalCenter: parent.verticalCenter
    }
    Text{
        anchors.left: parent.left
        anchors.leftMargin: 6
        anchors.verticalCenter: parent.verticalCenter
        text: elements[currentItem]
    }
    Rectangle{
        id: id_recExpand
        width: parent.width
        height: parent.height * elements.length
        radius: radiusNum
        anchors.top: parent.top
        anchors.topMargin: 0
        visible: isExpandDown ? true : false
        border.color: "gray"
        clip: true
        Component{
            id: highlight
            Rectangle {
                width: id_combobox.width; height: id_combobox.height
                z: 1
                opacity: 0.3
                color: isEnable ? "green" : "gray";
                radius: radiusNum
                y: id_listCombobox.currentItem.y
            }
        }

        ListView{
            id: id_listCombobox
            width: parent.width - 2
            height: parent.height - 2
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            model: elements
            highlight: highlight
            highlightFollowsCurrentItem: true
            delegate: Rectangle{
                width: parent.width
                height: id_combobox.height - 2
                color: "#F5FFFA"
                Text{
                    anchors.left: parent.left
                    anchors.leftMargin: 6
                    anchors.verticalCenter: parent.verticalCenter
                    text: elements[index]
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        id_listCombobox.currentIndex = index
                        currentItem = index
                        hideExpand();
                    }
                }
            }
        }
    }

    Rectangle{
        id: subRec
        anchors.fill: parent
        radius: radiusNum
        color: "transparent"
        opacity: 0.6
    }
    MouseArea{
        id: id_mouseSelectCB
        anchors.fill: parent
        z: 1
        onClicked: {
            // Expand the combo box
            isExpandDown = true;
            console.log("Expand the combobox")
            showExpand();
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
        enabled: isEnable
    }
    function hideExpand(){
        closeExpand();
        id_mouseSelectCB.visible = true;
        id_recExpand.visible = false;
    }
    function showExpand(){
        openCombobox();
        id_listCombobox.currentIndex = currentItem
        id_mouseSelectCB.visible = false;
        id_recExpand.visible = true;
    }

}
