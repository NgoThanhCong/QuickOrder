import QtQuick 2.0
import "../common"

BackgroundItem{
    property string title : ""
    property string subText: ""
    property string src: ""
    readonly property string passedColor: ms.color.state_accepted
    readonly property string failedColor: ms.color.state_rejected
    property bool isUp: false
    height: ms.item.height
    property alias icon: icon
    property alias text: txtTitle
    signal iconClicked()

    TextTitle{
        id : txtTitle
        text : title
        width: parent.width        
        font.weight: Font.DemiBold
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.right: subText !== "" ? txtSub.left : icon.left
    }

    Rectangle{
        id : ledStatus
        height: ms.textled.led_height
        width: height
        radius: ms.textled.led_radius
        color: txtSub.color
        visible: subText != ""
        anchors.verticalCenter: txtSub.verticalCenter
        anchors.right: txtSub.left
        anchors.rightMargin: 3
    }

    Text{
        id: txtSub
        text : subText
        visible: src === ""
        height: 19
        lineHeight: 19
        font.pixelSize: 14
        font.weight: Font.DemiBold
        anchors.verticalCenter: parent.verticalCenter
        color: subText === "Passed" ? passedColor : failedColor
        anchors.right: parent.right
        anchors.rightMargin: ms.margin.normal
    }

    ImageButton {
        id: icon
        height: 28
        width: 28
        visible: !txtSub.visible
        src: isUp ? "qrc:/icons/ic_arrow_up.png" : "qrc:/icons/ic_arrow_down.png"
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: ms.margin.normal
        onBtnClicked: iconClicked()
    }


}
