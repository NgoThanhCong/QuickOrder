import QtQuick 2.0
import "../common"
import QtGraphicalEffects 1.12

Item {
    id : rootCard
    height: 379
    width: 286

    CircularImage{
        id : itemImg
        height: 210
        width: 210
        radius: 210
        anchors.top: parent.top
        anchors.left: parent.left
        source: modelData.image
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

    Rectangle{
        height: 280
        width: 286
        z:-1
        radius: 30
        anchors{
            top:parent.top
            topMargin: 73
        }
        color: "white"

        Text{
            height: 38
            anchors.left: parent.left
            anchors.leftMargin: 16
            anchors.right: parent.right
            elide: Text.ElideRight
            font.pixelSize: 18
            anchors.top: parent.top
            anchors.topMargin: 140
            color: "black"
            text : modelData.name
            font.bold: true
            id : itemName
        }

        ThreeOptions{
            id : sizeOption
            anchors{
                top: itemName.bottom
                // topMargin: 4
                left: parent.left
                leftMargin: 16
            }
            dataOptions: [modelData.price, modelData.priceM ,modelData.priceL]
            onOption1Selected: {
                if(modelData.isTopping()){
                    orderController.addToppingItem(orderScreenRoot.currentItemIdx, modelData.itemId, 0)
                }else{
                    orderController.addOrderItem(modelData.itemId, 0)
                }
            }
            onOption2Selected: {
                if(modelData.isTopping()){
                    orderController.addToppingItem(orderScreenRoot.currentItemIdx, modelData.itemId, 1)
                }else{
                    orderController.addOrderItem(modelData.itemId, 1)
                }
            }
            onOption3Selected: {
                if(modelData.isTopping()){
                    orderController.addToppingItem(orderScreenRoot.currentItemIdx, modelData.itemId, 2)
                }else{
                    orderController.addOrderItem(modelData.itemId, 2)
                }
            }
        }
    }
}
