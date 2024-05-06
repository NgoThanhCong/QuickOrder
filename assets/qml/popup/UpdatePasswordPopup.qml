import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQml 2.3
import "../component"
import "../common"

PopupBase {
    id : rootPopup
    height: 240
    width: 480

    signal forceSync()
    property var catObj: null
    property bool isEditing: false

    Component.onCompleted: {
        popupTitle = "Input new Password"
    }

    onOpened: {
        inputConfirmPassowrd.textField.text = ""
        inputNewPassword.textField.text = ""
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
            txtTitle: "New Password"
            textField.text: ""
            id : inputNewPassword
            textField.onFocusChanged: {

            }
        }

        FormText{
            height: 36
            fontSize: 16
            width: parent.width
            txtTitle: "Confirm Password"
            textField.text: ""
            anchors.top: inputNewPassword.bottom
            anchors.topMargin: 16
            id : inputConfirmPassowrd
            textField.onFocusChanged: {

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
