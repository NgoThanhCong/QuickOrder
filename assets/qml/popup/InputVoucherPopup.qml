import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQml 2.3
import "../component"
import "../common"

PopupBase {
    id : rootPopup
    height: 200
    width: 420

    signal forceSync()
    property var catObj: null
    property bool isEditing: false

    Component.onCompleted: {
        popupTitle = "Input Voucher"
    }

    onOpened: {
        inputCode.textField.text = ""
        codeWarning.text = ""
    }

    Item{
        id : content_popup
        height: parent.height - bottomBar.height - titleBar.height
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
            txtTitle: "Code "
            textField.text: ""
            textField.onTextChanged: {
                textField.text = textField.text.toUpperCase()
                textField.text = textField.text.substring(0, 6);
            }
            id : inputCode
            textField.onFocusChanged: {
                if(textField.focus){
                    if(textField.color == "red")
                        textField.text = ""
                    resetTextField(inputCode)
                }
            }
            textField.validator: RegExpValidator { regExp: /^[a-zA-Z]*$/ }
        }

        TextNormal{
            id : codeWarning
            color: "#DD1E1E"
            text: ""
            height: text !== "" ? lineHeight : 0
            anchors{
                top: inputCode.bottom
                topMargin: ms.margin.short
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
                var code = inputCode.textField.text
                if(code.length == 6 && voucherModel.isCodeExisted(code))
                {
                    if(!orderController.applyVoucher(code)){
                        codeWarning.text = "Invalid Code";
                    }else{
                        close();
                    }
                }else{
                    codeWarning.text = "Invalid Code";
                }
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
