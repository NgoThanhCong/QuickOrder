import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    height: ms.icon.height
    width: height
    property string src: ""
    signal btnClicked()
    smooth: true
    antialiasing: true
    property alias icon: imgBtn
    property color btnColor: "black"

    Image{
        id: imgBtn
        height: ms.icon.height_ic
        width: ms.icon.width_ic
        source: src
        anchors.centerIn: parent
    }
    ColorOverlay{
        anchors.fill: imgBtn
        source:imgBtn
        color: btnColor
        antialiasing: true
        id : overlay
    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: [imgBtn,overlay]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [imgBtn,overlay]
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
