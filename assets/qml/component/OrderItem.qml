import QtQuick 2.0
import QtGraphicalEffects 1.12
import "../common"

Rectangle {
    id : root
    height: 90
    width: parent.width
    color: "transparent"
    border.color: isSelected ? "lightblue" : "transparent"
    border.width: 1
    property bool isSelected: listOrderItem.currentIndex == index


    CircularImage{
        id : itemImg
        height: 64
        width: 64
        source : image
        radius: 10
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 16
        }
    }

    DropShadow {
        anchors.fill: itemImg
        horizontalOffset: 1
        verticalOffset: 1
        radius: 3
        samples: 6
        color: "#60000000"
        source: itemImg
    }

    TextNormal{
        id : itemName
        height: 22
        anchors{
            top:  itemImg.top
            left: itemImg.right
            right: itemPrice.left
            margins: 8
            leftMargin: 16
            topMargin: -4
        }
        color: ms.color.black
        font.pixelSize: 22
        text : name + " (" + size + ") "
    }

    Counter{
        id : counter
        height: 30
        z:11
        anchors{
            top:  itemName.bottom
            left: itemImg.right
            margins: 8
            leftMargin: 16
            topMargin: 16
        }
        valueCounter: quantity
        onValueCounterChanged: {
            console.log("New Value: "+ id + " - " + valueCounter)
            if(quantity !== counter.valueCounter)
                orderController.updateOrderItem(id, valueCounter)
        }
    }

    TextNormal{
        id : itemPrice
        height: 22
        width: 60
        horizontalAlignment: Text.AlignRight
        anchors{
            top:  itemName.bottom
            right: parent.right
            margins: 8
            rightMargin: 16
        }
        text : price
        font.pixelSize: 18
        font.bold: true
    }

    LevelItem{
        id :sugarItem
        levelName: "Sugar"
        z:10
        anchors{
            verticalCenter: counter.verticalCenter
            right: itemPrice.left
            rightMargin: 16
        }
        levelIdx: sugarLevel
        onBtnClicked: orderModel.orderDataView.incSugar(index)
    }

    LevelItem{
        levelName: "Ice"
        z:10
        anchors{
            verticalCenter: counter.verticalCenter
            right: sugarItem.left
            rightMargin: 16
        }
        levelIdx: iceLevel
        onBtnClicked: orderModel.orderDataView.incIce(index)
    }

    MouseArea{
        z:1
        anchors.fill: parent
        onClicked: {
            listOrderItem.currentIndex = index
        }
    }

}
