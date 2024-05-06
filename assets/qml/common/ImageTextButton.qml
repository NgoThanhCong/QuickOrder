import QtQuick 2.12
import QtGraphicalEffects 1.0

Item{
    height: ms.icon.height
    width: height
    property string src: ""
    property string btnName: ""
    signal btnClicked()
    id : root

    Image{
        id: imgBtn
        height: ms.item.height
        width: height
        source: src
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        smooth: true
        antialiasing: true
    }

    Text{
        id : btnTitle
        text : btnName
        anchors.top: imgBtn.bottom
        anchors.topMargin: 6
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: ms.normalText.fontSize
        font.weight: Font.DemiBold
    }

    PropertyAnimation {
        id: scaleDownAnim
        target: root
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        target: root
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
