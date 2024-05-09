import QtQuick 2.12
import "../component"
import "../common"
import "../popup"
import QtQml 2.3
import QtQuick.Dialogs 1.3

Rectangle{
    id : root
    property var settingsController: SettingsScreenController
    property var settingsModel: SettingsScreenModel
    color: "#F9F9F9"

    CardBase{
        id : rootCard
        height: parent.height - 64
        width: parent.width - 64
        anchors.centerIn: parent

        Column{
            id : settingsContainer
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
                margins: 16
            }
            height: childrenRect.height
            spacing: 8

            TextTitle{
                id : titleSettings
                text: "Settings"
                font.pixelSize: 24
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width
                height: 40
            }

            FormText{
                height: 40
                fontSize: 18
                width: parent.width
                txtTitle: "Store Name"
                textField.text: settingsModel.storeName
                id : inputNameStore
                textField.onTextChanged: rootCard.checkChanges()
            }

            FormText{
                height: 40
                fontSize: 18
                width: parent.width
                txtTitle: "Address"
                textField.text: settingsModel.address
                id : inputAddress
                textField.onTextChanged: rootCard.checkChanges()
            }

            FormText{
                height: 40
                fontSize: 18
                width: parent.width
                txtTitle: "Hotline"
                textField.text: settingsModel.hotline
                id : inputHotline
                textField.onTextChanged: rootCard.checkChanges()
            }

            FormText{
                height: 40
                fontSize: 18
                width: parent.width
                txtTitle: "FanPage Link"
                textField.text: settingsModel.fanpage
                id : inputFbLink
                textField.onTextChanged: rootCard.checkChanges()
            }

            TextTitle{
                id : titleBankAccount
                text: "Bank Account"
                font.pixelSize: 24
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                width: parent.width
                height: 40
            }

            Image{
                id : qrCodeBanking
                anchors.horizontalCenter: parent.horizontalCenter
                source: settingsModel.bankId === "" ? "qrc:/images/select_avt.png" : settingsModel.bankId
                height: 500
                width: 500
                fillMode: Image.PreserveAspectFit
                MouseArea{
                    anchors.fill: parent
                    onClicked: fileDialog.open();
                }
                onSourceChanged: rootCard.checkChanges()
            }
        }

        function checkChanges(){
            let isUpdating = (inputNameStore.textField.text !== settingsModel.storeName
                                || inputHotline.textField.text !== settingsModel.hotline
                                || inputFbLink.textField.text !== settingsModel.fanpage
                                || inputAddress.textField.text !== settingsModel.address
                                || qrCodeBanking.source != settingsModel.bankId
                              )
            bottomBar.visible = isUpdating
        }

        Item{
            id : bottomBar
            height: ms.Popup.bottom_bar_height
            width: parent.width / 4
            anchors.top: settingsContainer.bottom
            anchors.topMargin: 16
            anchors.right: parent.right

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
                anchors.leftMargin: 40
                anchors.verticalCenter: parent.verticalCenter
                onBtnClicked: {
                    forceActiveFocus()
                    let storeName = inputNameStore.textField.text
                    let address = inputAddress.textField.text
                    let hotline = inputHotline.textField.text
                    let fanpage = inputFbLink.textField.text
                    let bankId = qrCodeBanking.source

                    settingsController.updateStoreName(storeName);
                    settingsController.updateHotline(hotline);
                    settingsController.updateFanpageLink(fanpage);
                    settingsController.updateAddress(address);
                    settingsController.updateBankId(bankId)
                    qrCodeBanking.source = settingsModel.bankId

                    rootCard.checkChanges();
                }
            }

            ButtonDefault{
                width: ms.button_default.width_extra
                name : "Cancel"
                anchors.right: parent.right
                anchors.verticalCenter: parent.verticalCenter
                anchors.rightMargin: 40
                onBtnClicked: {
                    inputNameStore.textField.text = settingsModel.storeName
                    inputHotline.textField.text = settingsModel.hotline
                    inputFbLink.textField.text = settingsModel.fanpage
                    inputAddress.textField.text = settingsModel.address
                    qrCodeBanking.source = settingsModel.bankId
                    rootCard.checkChanges();
                }
            }
        }
            Component.onCompleted: rootCard.checkChanges();
    }

    FileDialog {
        id: fileDialog
        title: "Select an Image"
        folder: shortcuts.pictures
        nameFilters: ["Image files (*.png)"]
        onAccepted: {
            console.log("Image Selected: ", fileDialog.fileUrl)
            qrCodeBanking.source = fileDialog.fileUrl
        }
    }

}
