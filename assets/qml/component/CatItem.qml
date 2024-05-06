import QtQuick 2.0
import "../common"
import QtGraphicalEffects 1.12

Item {
    height: 80
    width: 67
    antialiasing: true
    id :rootCard
    property bool isSelected: false
    signal btnClicked(var catId)

    Rectangle{
        anchors.fill: parent
        radius: 18
        antialiasing: true
        id : bg
        color: isSelected ? ms.color.primary : ms.color.white
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

    Image{
        id : iconCat
        height: 32
        width: 32
        anchors{
            top: parent.top
            topMargin: 16
            horizontalCenter: parent.horizontalCenter
        }
        source: "qrc:/icons/ic_bubble_tea.png"
    }

    TextNormal{
        anchors{
            top: iconCat.bottom
            left: parent.left
            right: parent.right
            margins: 8
        }
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        text : modelData.name
        color: isSelected ? "white" : "black"
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
        onClicked: {
            btnClicked(modelData.categoryId)
            catLv.idxSelected = catLv.idxSelected == index ? -1 : index
        }
    }
}
