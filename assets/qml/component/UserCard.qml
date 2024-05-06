import QtQuick 2.0
import QtGraphicalEffects 1.12
import "../common"
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.3
import QtQml 2.3
import "../popup"

Item {
    id : rootCard
    height: 320
    antialiasing: true
    property bool isEditing: false

    Rectangle{
        id: bg
        anchors.fill: parent
        radius: 10
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


    function resetTextField(input, text){
        input.textField.color = "black"
        input.textField.font.bold = false
        input.textField.text = text
    }

    function clearEditing(){
        resetTextField(inputName, modelData.name)
        resetTextField(inputAdr, modelData.adr)
        resetTextField(inputPhone, modelData.phone)
        resetTextField(inputDob, modelData.dob)
        resetTextField(inputHireDate, modelData.hireDate)
        imgAvatar.source = modelData.avatar
        isEditing = false
    }

    function checkingIsEditing()
    {
        isEditing = !(inputName.textField.text === modelData.name
                      && inputAdr.textField.text === modelData.adr
                      && inputPhone.textField.text === modelData.phone
                      && inputDob.textField.text === modelData.dob
                      && inputHireDate.textField.text === modelData.hireDate
                      && imgAvatar.source == modelData.avatar)
    }

    function isValidDateFormat(dateString) {
        var regex = /^(0[1-9]|[1-2][0-9]|3[0-1])\/(0[1-9]|1[0-2])\/\d{4}$/;
        return regex.test(dateString);
    }

    function isValidVietnamesePhoneNumber(phoneNumber) {
        var phoneNumberRegex = /^(03|05|07|08|09)[0-9]{8}$/;
        return phoneNumberRegex.test(phoneNumber);
    }

    FileDialog {
        id: fileDialog
        title: "Select an Image"
        folder: shortcuts.pictures
        nameFilters: ["Image files (*.png)"]
        onAccepted: {
            console.log("Image Selected: ", fileDialog.fileUrl)
            imgAvatar.source = fileDialog.fileUrl
        }
    }

    ImageButton{
        id : btnClose
        src: "qrc:/icons/ic_close.png"
        onBtnClicked: {
            confirmationPopup.confirmPopupData = modelData.userId
            confirmationPopup.open()
        }
        anchors.right: parent.right
        btnColor: "black"
        visible: modelData.userType !== 0
        z:10
    }

    Image{
        id : imgAvatar
        height: 200
        width: 200
        source: modelData.avatar
        anchors.verticalCenterOffset: 0
        anchors.topMargin: 0
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.top: parent.top
        fillMode: Image.PreserveAspectFit
        anchors.leftMargin: 50
        MouseArea{
            anchors.fill: parent
            onClicked: fileDialog.open()
        }
        onSourceChanged: checkingIsEditing()
    }

    Item{
        height: parent.height - 32
        anchors.left: imgAvatar.right
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        Column{
            id : leftContainer
            height: childrenRect.height
            width: parent.width/2 - 32
            anchors.left: parent.left
            anchors.leftMargin : 16
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

                FormText{
                    height: 40
                    width: parent.width
                    txtTitle: "User Type : "
                    textField.text: modelData.userType === 0 ? "Admin" : "Staff"
                    textField.enabled: false
                    textField.background: Item{}
                    formDisable: true
                }

                FormText{
                    height: 40
                    width: parent.width
                    txtTitle: "User Name : "
                    textField.text: modelData.userName
                    textField.enabled: false
                    textField.background: Item{}
                    formDisable: true
                }

                FormText{
                    id : inputName
                    height: 40
                    width: parent.width
                    txtTitle: "Name : "
                    textField.text: modelData.name
                    textField.onTextChanged: checkingIsEditing()
                }

                FormText{
                    id : inputAdr
                    height: 40
                    width: parent.width
                    txtTitle: "Address : "
                    textField.text: modelData.adr
                    textField.onTextChanged: checkingIsEditing()
                }
        }

        Column{
            height: childrenRect.height
            width: (parent.width - 32) /2
            anchors.right: parent.right
            anchors.rightMargin: 32
            anchors.top: leftContainer.top
            spacing: 8
                FormText{
                    id : inputPhone
                    height: 40
                    width: parent.width
                    txtTitle: "Phone : "
                    textField.text: modelData.phone
                    textField.onTextChanged: checkingIsEditing()
                }

                FormText{
                    id : inputDob
                    height: 40
                    width: parent.width
                    txtTitle: "Birthday : "
                    textField.text: modelData.dob
                    textField.onTextChanged: checkingIsEditing()
                }

                FormText{
                    id : inputHireDate
                    height: 40
                    width: parent.width
                    txtTitle: "Hire Date : "
                    textField.text: modelData.hireDate
                    textField.onTextChanged: checkingIsEditing()
                }

                ButtonDefault{
                    height: 40
                    width: 120
                    name : "Update Password"
                    onBtnClicked: {
                        updatePasswordPopup.open();
                    }
                }

                Item{
                    height: 40
                    width: parent.width
                    visible: isEditing

                    ButtonDefault{
                        id : btnOk
                        width: ms.button_default.width_extra
                        name : "Ok"
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
                        onBtnClicked: {
                            forceActiveFocus()
                            console.log("Edit Done")
                            var dob = inputDob.textField.text
                            var phone = inputPhone.textField.text
                            var hireDate = inputHireDate.textField.text
                            var name = inputName.textField.text
                            var address = inputAdr.textField.text
                            var imgAvt = imgAvatar.source

                            var isValidUser = true;

                            if(!isValidDateFormat(dob)){
                                inputDob.textField.color = "red"
                                inputDob.textField.font.bold = true
                                isValidUser = false;
                                console.log("dob Invalid")
                            }

                            if(!isValidDateFormat(hireDate)){
                                inputHireDate.textField.color = "red"
                                inputHireDate.textField.font.bold = true
                                isValidUser = false;
                                console.log("hireDate Invalid")
                            }

                            if(!isValidVietnamesePhoneNumber(phone)){
                                inputPhone.textField.color = "red"
                                inputPhone.textField.font.bold = true
                                isValidUser = false;
                                console.log("phone Invalid")
                            }

                            if(name.length === 0){
                                inputName.textField.color = "red"
                                inputName.textField.font.bold = true
                                isValidUser = flase
                            }

                            if(address.length === 0){
                                inputAdr.textField.color = "red"
                                inputAdr.textField.font.bold = true
                                isValidUser = flase
                            }

                            if(isValidUser){
                                var isUpdateOk = userController.updateUser(modelData.userName, name, dob,
                                                                           address, phone, hireDate, imgAvt)
                                console.log("Update Result: ", isUpdateOk)
                                if(isUpdateOk){
                                    userController.syncData()
                                    rootCard.isEditing = false
                                }
                            }

                        }
                    }

                    ButtonDefault{
                        width: ms.button_default.width_extra
                        name : "Cancel"
                        anchors.right: btnOk.left
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.rightMargin: 40
                        onBtnClicked: {
                            console.log("Cancel Editing")
                            clearEditing();
                        }
                    }
                }
        }
    }
}
