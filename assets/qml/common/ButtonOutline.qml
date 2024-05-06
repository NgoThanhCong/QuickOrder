import QtQuick 2.0

Rectangle {
    id : root
    height: ms.button_outline.height
    width: ms.button_outline.width
    radius: ms.button_outline.radius
    property bool isActive: true
    color : {
        if(!root.enabled) return "grey"
        return isActive ? ms.color.primary : Qt.rgba(10/255, 61/255, 152/255, 0.05)
    }

    property string name : ""
    signal btnClicked()

    TextNormal{
        anchors.fill: parent
        color: isActive ? "white" : ms.color.primary
        opacity: isActive ? 1 : 0.8
        text: name
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.weight: Font.DemiBold
    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: root
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: root
        properties: "scale"
        from: 0.9
        to: 1.0
        duration: 100
        onStopped: btnClicked()
    }

    MouseArea{
        z:1
        anchors.fill: parent
        onEntered: scaleDownAnim.restart()
        onReleased: scaleUpAnim.restart()
    }

}
