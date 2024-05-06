import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQml 2.3
import "../component"
import "../common"

PopupBase {
    id : rootPopup
    height: 260
    width: 420

    signal forceSync()
    property var catObj: null
    property bool isEditing: false

    Component.onCompleted: {
        popupTitle = "Add Vouchers"
    }

    onOpened: {
        inputValue.textField.text = ""
        inputExpiredDate.textField.text = ""
        inputQuantity.textField.text = ""
    }

    Column{
        id : content_popup
        height: parent.height - bottomBar.height - titleBar.height
        spacing: 8
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: 8
            rightMargin: 8
            bottom: bottomBar.top
        }
        FormText{
            height: 36
            fontSize: 16
            width: parent.width
            txtTitle: "Value (%)"
            textField.text: ""
            id : inputValue
            textField.validator: IntValidator { bottom: 1; top: 99 }

            textField.onFocusChanged: {
                if(textField.focus){
                    if(textField.color == "red")
                        textField.text = ""
                    resetTextField(inputValue)
                }
            }
        }

        FormText{
            height: 36
            fontSize: 16
            width: parent.width
            txtTitle: "Quantity"
            textField.text: ""
            textField.validator: IntValidator { bottom: 1; top: 99 }
            id : inputQuantity
            textField.onFocusChanged: {
                if(textField.focus){
                    if(textField.color == "red")
                        textField.text = ""
                    resetTextField(inputQuantity)
                }
            }
        }

        FormText{
            height: 36
            fontSize: 16
            width: parent.width
            txtTitle: "Expired Date "
            textField.text: ""
            textField.placeholderText: "dd/mm/yyyy"
            id : inputExpiredDate
            textField.onFocusChanged: {
                if(textField.focus){
                    if(textField.color == "red")
                        textField.text = ""
                    resetTextField(inputExpiredDate)
                }
            }
        }
    }

    Item{
        id : bottomBar
        height: ms.Popup.bottom_bar_height
        width: childrenRect.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Rectangle{
            height: ms.Popup.div_width
            width: parent.width
            color: ms.color.stroke
            anchors.top: parent.top
        }

        ButtonDefault{
            id : btnAdd
            width: ms.button_default.width_extra
            name : "Ok"
            anchors.left: parent.left
            anchors.leftMargin: ms.margin.normal
            anchors.verticalCenter: parent.verticalCenter
            onBtnClicked: {
                forceActiveFocus()
                var isValidVoucher = true;
                var expiredDate = inputExpiredDate.textField.text
                var value = inputValue.textField.text
                var quantity = inputQuantity.textField.text

                if(!isValidDateFormat(expiredDate) || !isDateGreaterThanOrEqualToToday(expiredDate)){
                    inputExpiredDate.textField.color = "red"
                    inputExpiredDate.textField.font.bold = true
                    isValidVoucher = false;
                    console.log("dob Invalid")
                }

                if(value.length == 0){
                    inputValue.textField.color = "red"
                    inputValue.textField.font.bold = true
                    isValidVoucher = false;
                }

                if(quantity.length == 0){
                    inputQuantity.textField.color = "red"
                    inputQuantity.textField.font.bold = true
                    isValidVoucher = false;
                }

                if(!isValidVoucher){
                    console.log("Not valid Data");
                    return;
                }

                voucherController.generateVoucher(value, quantity, expiredDate);
                voucherController.syncData()

                close();
            }
        }

        ButtonDefault{
            width: ms.button_default.width_extra
            name : "Cancel"
            anchors.left: btnAdd.right
            anchors.leftMargin: 32
            anchors.verticalCenter: parent.verticalCenter
            onBtnClicked: {
                close();
            }
        }
    }
}
