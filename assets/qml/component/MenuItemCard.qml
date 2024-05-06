import QtQuick 2.0
import "../common"
import QtGraphicalEffects 1.12

Item {
    id : menuItemCard
    height: 72
    width: parent.width

    Rectangle{
        id : bg
        anchors{
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            margins: 4
        }

        color: "white"
        radius: 5
    }

    DropShadow {
        anchors.fill: bg
        horizontalOffset: 1
        verticalOffset: 1
        radius: 4
        samples: 17
        color: "#60000000"
        source: bg
    }

    Row{
        anchors.fill: parent
        anchors.left: parent.left
        anchors.leftMargin: 20
        spacing: 8

        Image{
            height: 48
            width: 80
            source: modelData.image
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
        }

        TagInfo{
            width: 320
            textContent: modelData.name
        }

        TagInfo{
            textTitle: "Description"
            textContent: modelData.description
        }

        TagInfo{
            textTitle: "Category"
            textContent: menuModel.getCatById(modelData.categoryId)
        }

        TagInfo{
            textTitle: "Size S"
            textContent: modelData.price
            width: 120
        }

        TagInfo{
            textTitle: "Size M"
            textContent: modelData.priceM
            width: 120
        }

        TagInfo{
            textTitle: "Size L"
            textContent: modelData.priceL
            width: 120
        }

        Item {
            height: parent.height
            width: parent.width / 4
        }

        ImageButton{
            id : btnEdit
            src: "qrc:/icons/ic_edit.png"
            width: 40
            height: 40
            onBtnClicked: {
                addMenuItemPopup.dataMenuItem = modelData
                addMenuItemPopup.isEditMode = true
                addMenuItemPopup.open()
            }
            anchors.verticalCenter: parent.verticalCenter
            btnColor: "black"
            z:10
        }

        ImageButton{
            src: "qrc:/icons/ic_close.png"
            width: 40
            height: 40
            onBtnClicked: {
                confirmRemoveMenuItemPopup.confirmPopupData = modelData.itemId
                confirmRemoveMenuItemPopup.open()
            }
            anchors.verticalCenter: parent.verticalCenter
            btnColor: "black"
            z:10
        }
    }
}
