import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id : rootCard
    property string title : ""
    property string value: ""
    signal btnClicked()

    TextNormal{
        anchors.top: parent.top
        anchors.topMargin: -4
        text : title
        color: "black"
        font.bold: true
        z:10
        font.pixelSize: 16
        width: content.width
        horizontalAlignment: Text.AlignHCenter
    }

    Item{
        id : content
        height: 60
        width: 60


        Rectangle{
            anchors.fill: parent
            radius: 50
            color: "#F8F8F8"
            antialiasing: true
            id : bg
        }

        DropShadow {
            anchors.fill: bg
            horizontalOffset: 1
            verticalOffset: 1
            radius: 3
            samples: 6
            color: "#60000000"
            source: bg
        }
        Text {
            anchors.centerIn: parent
            text: value
        }



    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: [rootCard]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [rootCard]
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
