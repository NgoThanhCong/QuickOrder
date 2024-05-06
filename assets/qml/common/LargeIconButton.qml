import QtQuick 2.0
import QtGraphicalEffects 1.0

Rectangle {
    id : imgBtn
    height: ms.large_icon_button.height
    width: ms.large_icon_button.width
    radius: ms.large_icon_button.radius
    border.width: isActive ? 0 : 1
    border.color: ms.color.stroke
    color: isActive ? Qt.rgba(10/255, 61/255, 152/255, 0.05) : "white"
    property bool isActive: false
    property string ic_src: ""
    property string btn_name : ""
    signal btnClicked()

    Image{
        id : icon
        height: ms.icon.height_sml
        width: height
        anchors{
            left: parent.left
            leftMargin: ms.margin.normal
            verticalCenter: parent.verticalCenter
        }
        source: ic_src

    }

    ColorOverlay{
       id : overlay
       anchors.fill: icon
       source: icon
       color: isActive ? ms.color.primary : ms.color.gray
    }

    TextSubTitle{
        anchors{
            left: icon.right
            leftMargin: ms.margin.short
            verticalCenter: parent.verticalCenter
        }
        text : btn_name
        font.weight: Font.DemiBold
        color: isActive ? ms.color.primary : ms.color.gray
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
