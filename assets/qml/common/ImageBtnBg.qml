import QtQuick 2.12
import QtGraphicalEffects 1.0

Rectangle {
    height: ms.icon.height
    width: height
    property string src: ""
    signal btnClicked()
    smooth: true
    antialiasing: true
    property alias icon: imgBtn
    property color btnColor: "black"
    color: ms.color.primary
    radius: 10


    Image{
        id: imgBtn
        anchors.fill: parent
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
