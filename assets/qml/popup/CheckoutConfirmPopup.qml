import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../common"
import ".."

Popup{
    id :  popup_base
    height: isCash ? 310 : 680
    width: 360
    anchors.centerIn: parent
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    margins: 0
    padding: 0
    property string popupTitle: "CHECKING OUT"
    property alias titlePopup: _titlePopup
    property string confirmPopupData: ""
    property bool isCash: true

    signal discard();
    signal confirm(var data);

    onOpened: {
        inputPaid.textField.text = ""
        updateChange()
    }

    background: Rectangle{
        anchors.fill: parent
        radius: ms.Windows.radius
        color: ms.color.white
    }

    Overlay.modal: Rectangle {
        color: Qt.rgba(0,0,0,0.5)
    }

    function updateChange(){
        let paid = parseFloat(inputPaid.textField.text);
        if(isNaN(paid)) paid = 0;
        let total = parseFloat(orderModel.total);
        let change = paid - total;
        changeTxt.numb = change.toFixed(2);
        btnAdd.enabled =  paid >= total;

        orderModel.change = changeTxt.numb;
        orderModel.cash = inputPaid.textField.text;
        console.log(orderModel.cash)
        orderModel.paymentMethod = isCash ? 0 : 1
    }

    Item{
        id : titlePopup
        height: ms.Popup.title_height
        width: parent.width
        TextTitle{
            id : _titlePopup
            anchors.left: parent.left
            anchors.leftMargin: ms.margin.normal
            text: popupTitle
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: ms.Popup.title_pixelSize
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item{
        id : content_cash
        visible: isCash
        anchors{
            top: titlePopup.bottom
            bottom: bottomBar.top
            left: parent.left
            right: parent.right
            margins: 4
            rightMargin: 16
        }

        ItemTextContentNumb{
            id : totalTxt
            anchors{
                top: parent.top
                topMargin: 8
            }

            height: 32
            width: parent.width
            title : "Total"
            numb: orderModel.total
        }

        FormText{
            id : inputPaid
            anchors{
                top: totalTxt.bottom
                topMargin: 32
                left: parent.left
                leftMargin: ms.margin.normal
                right: parent.right
                rightMargin: 8
            }
            height: 40            
            txtTitle: "Paid"
            color: ms.color.gray            
            textField.onTextChanged: updateChange()
            textField.validator: RegExpValidator { regExp: /^-?\d*\.?\d{0,2}$/ }
            textField.placeholderText: "0.00"
            textField.horizontalAlignment: Text.AlignRight
        }

        Rectangle{
            height: 1
            width: parent.width / 2
            radius: 10
            anchors.right: parent.right
            anchors.rightMargin: 16
            color: ms.color.stroke
            anchors.margins: 8
            anchors.top: inputPaid.bottom
            anchors.topMargin: 28
        }

        ItemTextContentNumb{
            id : changeTxt
            anchors{
                top: inputPaid.bottom
                topMargin: 42
            }
            height: 32
            width: parent.width
            title : "Change"
            numb : orderModel.total
        }

    }

    Item{
        id : content_banking
        visible: !isCash
        anchors{
            top: titlePopup.bottom
            bottom: bottomBar.top
            left: parent.left
            right: parent.right
            margins: 4
            rightMargin: 16
        }

        Image {
            id: qrCodeImg
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/qr_code_default.png"
        }

    }

    Item{
        id : bottomBar
        height: ms.Popup.bottom_bar_height
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Rectangle{
            height: ms.Popup.div_width
            width: popup_base.width
            color: ms.color.stroke
            anchors.top: parent.top
        }

        ButtonDefault{
            id : btnAdd
            width: ms.button_default.width_extra
            name : "Done"
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            enabled: false
            onBtnClicked: {
                forceActiveFocus()
                confirm(confirmPopupData)
                close()
            }
        }

        ButtonDefault{
            width: ms.button_default.width_extra
            name : "Cancel"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 40
            onBtnClicked: {
                discard()
                close();
            }
        }
    }    
}
