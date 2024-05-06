import QtQuick 2.0
import "../common"
import "../component"

CardBase {
    height: 120
    width: 240
    property string title : ""
    property string contentTxt: ""
    property string colorStatus : "yellow"

    Rectangle{
        id : status
        height: 16
        width: 16
        radius: 32
        anchors.left: parent.left
        anchors.leftMargin: 8
        anchors.verticalCenter: titleTxt.verticalCenter
        color: colorStatus
    }

    TextTitle{
        id : titleTxt
        text : title
        font.pixelSize: 14
        verticalAlignment: Text.AlignVCenter
        height: 32
        anchors{
            right: parent.right
            left: status.right
            leftMargin: 8
            top: parent.top
        }
        color: ms.color.gray
    }

    TextNumb{
        id : numbTxt
        text : contentTxt
        font.pixelSize: 20
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        anchors {
            top: titleTxt.bottom
            bottom: parent.bottom
            right: parent.right
            left: parent.left
            leftMargin: 16
        }
    }
}
