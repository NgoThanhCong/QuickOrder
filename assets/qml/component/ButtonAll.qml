import QtQuick 2.0
import "../common"

Rectangle {
    id : imgBtn
    width: ms.MainScreen.filter.all_width
    height: 28
    radius: 9
    border.width: 1
    anchors.verticalCenter: parent.verticalCenter
    anchors.right: btnPassFilter.left
    anchors.rightMargin: ms.margin.margin_10
    property bool isSelected: false
    border.color: isSelected ? "#004AAD" : ms.color.stroke
    signal btnClicked()

    TextNormal{
        text : "All"
        height: 28
        width: 16
        anchors.centerIn: parent
        color: btnAll.isSelected ? "#004AAD" : ms.color.black
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: [imgBtn]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [imgBtn]
        properties: "scale"
        from: 0.9
        to: 1.0
        duration: 100
    }

    MouseArea{
        z:1
        anchors.fill: parent
        onEntered: scaleDownAnim.restart()
        onReleased: scaleUpAnim.restart()
        onClicked: btnClicked()
    }
}
