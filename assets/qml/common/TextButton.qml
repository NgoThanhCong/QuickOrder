import QtQuick 2.0
import QtGraphicalEffects 1.0

Item {
    id : root
    height: 32
    width: 148
    property string ic_src : ""
    property string btn_name: ""
    property alias textColor: btnName.color
    signal btnClicked()

    Image{
        id : icon
        source: ic_src
        height: ms.icon.height_ic
        width: height
        anchors{
            left: parent.left
            leftMargin: ms.margin.medium_short
        }

        anchors.verticalCenter: parent.verticalCenter

        ColorOverlay{
            anchors.fill: parent
            color: ms.color.primary
            source: parent
        }

    }

    TextNormal {
        id: btnName
        text: btn_name
        anchors.verticalCenter: parent.verticalCenter
        height: ms.icon.height_ic
        anchors{
            left: icon.right
            leftMargin: ms.margin.extra_short
            right: parent.right
        }
        color: ms.color.primary
        font.weight: Font.DemiBold
        opacity: 0.8
    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: [root]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [root]
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
