import QtQuick 2.0

Rectangle {
    id : root
    height: ms.button_default.height
    width: ms.button_default.width
    color : {
        if(!root.enabled) return "grey"
        if(mouseArea.pressed) return ms.color.primary
        if(mouseArea.containsMouse) return "#004199"
        return Qt.rgba(0, 74/255, 173/255, 1)
    }

    radius: ms.button_default.radius
    property string name : ""
    signal btnClicked()

    TextNormal{
        anchors.fill: parent
        color: ms.color.white
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
        id : mouseArea
        z:1
        anchors.fill: parent
        onEntered: scaleDownAnim.restart()
        onReleased: scaleUpAnim.restart()
    }

}
