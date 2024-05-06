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

        TagInfo{
            width: parent.width * 0.2
            textContent: modelData.voucherCode
        }

        TagInfo{
            width: parent.width * 0.2
            textContent: modelData.discountValue + "%"
        }

        TagInfo{
            width: parent.width * 0.2
            textContent: modelData.getStatusText()
        }

        TagInfo{
            width: parent.width * 0.2        
            textContent: modelData.validDate
        }
    }

    ImageButton{
        src: "qrc:/icons/ic_close.png"
        width: 40
        height: 40
        visible: modelData.status !== 1
        anchors{
            right: bg.right
            rightMargin: 32
            verticalCenter: parent.verticalCenter
        }

        onBtnClicked: {
            confirmDeleteVoucher.confirmPopupData = modelData.voucherId
            confirmDeleteVoucher.open()
        }
        btnColor: "black"
        z:10
    }
}
