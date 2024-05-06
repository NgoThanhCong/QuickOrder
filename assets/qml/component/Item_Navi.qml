import QtQuick 2.12
import QtGraphicalEffects 1.0

Item {
    id : root
    height: ms.icon.height
    property bool isHighlight: true
    property bool enable: false
    property string icSrc: ""
    property string title: ""
    signal itemClicked()
    property string primativeColor: isHighlight ? "#004AAD" : "#778A96"

    Image{
        id : icon
        height: ms.icon.height_sml
        width: height
        anchors.top: parent.top
        anchors.topMargin: ms.margin.margin_10
        anchors.horizontalCenter: parent.horizontalCenter
        source: icSrc
        smooth: true
        antialiasing: true
    }

    ColorOverlay{
        anchors.fill: icon
        source:icon
        color: primativeColor
        antialiasing: true
        id : overlay
    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: [icon, overlay]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [icon, overlay]
        properties: "scale"
        from: 0.9
        to: 1.0
        duration: 100
    }

    Text{
        id : titleItem
        font.pixelSize: ms.normalText.fontSize
        lineHeight: ms.normalText.lineHeight
        color: primativeColor
        text: title
        anchors.top: parent.top
        anchors.topMargin: ms.NavigationBar.navi_item.title_top_margin
        anchors.horizontalCenter: parent.horizontalCenter
    }

    //Highlight
    Rectangle{
        visible: isHighlight
        anchors.left: parent.left
        width: ms.NavigationBar.navi_item.border_width
        height: parent.height
        color: ms.color.primary
        id: highlightBorder
    }
    Rectangle{
        visible: isHighlight
        anchors.left: highlightBorder.right
        width: ms.NavigationBar.navi_item.gradient_width
        height: parent.height

        gradient: Gradient{
            GradientStop{position: 0.0; color:"#1A004AAD"}
            GradientStop{position: 1.0; color:"#00004AAD"}
            orientation: Gradient.Horizontal
        }
    }

    MouseArea{
        visible: enable
        anchors.fill: parent
        onClicked: itemClicked()
        onEntered: scaleDownAnim.restart()
        onReleased: scaleUpAnim.restart()
    }
}
