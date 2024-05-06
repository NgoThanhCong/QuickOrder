import QtQuick 2.0
import QtGraphicalEffects 1.12
import "../common"

Rectangle {
    id : root
    height: 40
    width: parent.width
    color: "transparent"
    border.color: isSelected ? "lightblue" : "transparent"
    border.width: 1
    property bool isSelected: listOrderItem.currentIndex == index
    property var toppingModel : []

    ImageButton{
        src: "qrc:/icons/ic_close.png"
        width: 30
        height: 30
        onBtnClicked: orderController.removeToppingItem(id)
        anchors.verticalCenter: parent.verticalCenter
        btnColor: "black"
        z:10
        anchors.left: parent.left
        anchors.leftMargin: 16
    }

    CircularImage{
        id : itemImg
        width: 36
        height: 36
        source : image
        radius: 36
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 80
        }
    }

    TextNormal{
        id : itemName
        height: 36
        anchors{
            top:  itemImg.top
            left: itemImg.right
            right: itemPrice.left
            margins: 8
            leftMargin: 16
            topMargin: -4
            verticalCenter: parent.verticalCenter
        }
        color: ms.color.black
        font.pixelSize: 16
        text : name + " (" + size + ") " + "x" + quantity
    }

    TextNormal{
        id : itemPrice
        height: 36
        width: 60
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        anchors{
            top: parent.top
            right: parent.right            
            rightMargin: 16
        }
        text : price
        font.pixelSize: 12
        font.weight: Font.Medium
    }

    MouseArea{
        z:1
        anchors.fill: parent
        onClicked: {
            listOrderItem.currentIndex = index
        }
    }

}
