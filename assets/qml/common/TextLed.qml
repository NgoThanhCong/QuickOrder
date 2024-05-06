import QtQuick 2.0

Item {
    width: ms.textled.width
    height: ms.textled.height
    property bool passed: true
    property string passedColor: ms.color.state_accepted
    property string failedColor: ms.color.state_rejected
    property string passedContent: "Accepted"
    property string failedContent: "Rejected"
    property alias text: txtSub

    Rectangle{
        id : ledStatus
        height: ms.textled.led_height
        width: height
        radius: ms.textled.led_radius
        color: txtSub.color
        anchors.verticalCenter: txtSub.verticalCenter
        anchors.left: parent.left
    }

    TextNormal{
        id: txtSub
        height: ms.normalText.lineHeight
        font.pixelSize: ms.normalText.fontSize
        anchors.verticalCenter: parent.verticalCenter
        text: passed ? passedContent : failedContent
        color: passed ? passedColor : failedColor
        anchors.left: ledStatus.right
        anchors.leftMargin: ms.margin.extra_short
    }
}
