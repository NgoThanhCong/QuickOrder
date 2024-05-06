import QtQuick 2.9
import "../common"

CardBase {
    height: 260

    ListView{
        id : bestSellerLv
        height: 252
        width: parent.width
        spacing: 4
        model : reportModel.bestSellerItems
        headerPositioning: ListView.OverlayHeader
        header : Rectangle {
            height: 40
            z:10
            anchors{
                left: parent.left
                right: parent.right
                margins: 16
            }

            TextTitle{
                anchors.fill: parent
                text: "Best Seller"
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 20
                color: ms.color.primary
            }
        }

        clip : true

        delegate: Item {
            height: 32
            anchors{
                left: parent.left
                right: parent.right
                margins: 16
            }

            TextNormal{
                id : nameTxt
                height: parent.height
                width: parent.width /2
                text: modelData.itemName
                anchors{
                    left: parent.left
                    top: parent.top
                }
                font.pixelSize: index == 0 ? 16 : ms.normalText.fontSize
                font.bold: index == 0
                verticalAlignment: Text.AlignVCenter
            }

            Image{
                id : crown
                anchors.right: txtNumb.left
                anchors.rightMargin: 8
                source: "qrc:/icons/ic_crown.png"
                height: parent.height
                width: height
                fillMode: Image.PreserveAspectFit
                visible: index == 0
            }


            TextNumb{
                id : txtNumb
                height: parent.height
                anchors.right: parent.right
                text : modelData.quantity
            }

            Rectangle{
                height: 1
                width: parent.width
                radius: 10
                color: ms.color.stroke
                anchors.bottom: parent.bottom
            }
        }
    }

}
