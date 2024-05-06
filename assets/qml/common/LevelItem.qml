import QtQuick 2.0

Rectangle{
    id : levelItem
    height: 40
    width: 40
    radius: 46
    border.width: 1
    border.color: "lavender"
    property string levelName : ""
    antialiasing: true
    signal btnClicked()

    property int levelIdx: 2
    property var levels: [lv0,lv1,lv2]

    TextSubTitle {
        id: name
        text: levelName
        anchors.centerIn: parent
        font.bold: false
        font.pixelSize: 12
    }

    Gradient{
        id : lv0
        GradientStop { position: 1.0; color: "transparent" }
        GradientStop { position: 0.0; color: "transparent" }
    }

    Gradient{
        id : lv1
        GradientStop { position: 1.0; color: "lavender" }
        GradientStop { position: 0.6; color: "lavender" }
        GradientStop { position: 0.5; color: "transparent" }
        GradientStop { position: 0.0; color: "transparent" }
    }

    Gradient{
        id : lv2
        GradientStop { position: 1.0; color: "lavender" }
        GradientStop { position: 0.0; color: "lavender" }
    }

    gradient: levels[levelIdx]

    PropertyAnimation {
        id: scaleDownAnim
        targets: [levelItem]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [levelItem]
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
