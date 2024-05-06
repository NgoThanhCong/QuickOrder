import QtQuick 2.12
import "../common"
import "../component"
import "../popup"

Rectangle{

    property var voucherController: VoucherScreenController
    property var voucherModel: VoucherScreenModel
    color: "#F9F9F9"

    TextTitle{
        id : titleCategory
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            margins : 8
        }
        text: "Voucher"
        font.pixelSize: 24
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width
        height: 40
    }

    ConfirmationPopup{
        width: 680
        id : removeCatConfirmationPopup
        popupTitle: "All Menu Item unders this Category will be deleted !"
        titlePopup.color: "red"
        onConfirm: {

        }
    }

    Item {
        id : header
        height: 48
        width: parent.width
        anchors.top: titleCategory.bottom
        anchors.topMargin: 8

        Row{
            anchors.fill: parent
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 8

            TagInfo{
                width: parent.width * 0.2
                textContent: "Voucher Code"
                isHeader: true
            }

            TagInfo{
                width: parent.width * 0.2
                textContent: "Discount Value"
                isHeader: true
            }

            TagInfo{
                width: parent.width * 0.2
                textContent: "Status"
                isHeader: true
            }

            TagInfo{
                width: parent.width * 0.2
                textContent: "Expired Date"
                isHeader: true
            }

            Item {
                height: 50
                width: parent.width * 0.2
                ButtonDefault{
                    name : "Add Voucher"
                    height: 36
                    width: 120
                    anchors.right: parent.right
                    anchors.rightMargin: 48
                    onBtnClicked: {
                        addVouncherPopup.open()
                    }
                }
            }
        }
    }

    AddVoucherPopup{
        id : addVouncherPopup
    }

    ListView{
        id : menuItemLv
        clip: true
        spacing: 0
        anchors{
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: parent.bottom
            margins: 8
        }
        model : voucherModel.vouchers
        snapMode: ListView.SnapToItem
        delegate: VoucherItem{

        }
    }

    ConfirmationPopup{
        id : confirmDeleteVoucher
        onConfirm: {
            voucherController.removeVoucher(confirmPopupData)
            voucherController.syncData()
        }
    }
}
