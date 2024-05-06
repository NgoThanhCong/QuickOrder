import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQml 2.3
import "../component"
import "../common"

PopupBase {
    id : basePopup

    signal forceSync()

    Component.onCompleted: {
        popupTitle = "Add New User"
    }

    onOpened: {
        // Cong TODO
        console.log("Opened")
        inputName.textField.text = ""
        inputAddress.textField.text = ""
        inputDob.textField.text = ""
        inputPhone.textField.text = ""
        inputHireDate.textField.text = ""
        inputUserName.textField.text = ""
        inputPassword .textField.text = ""
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

    Item{
        id : content_popup
        height: parent.height - bottomBar.height - titleBar.height
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: 64
            rightMargin: 64
            bottom: bottomBar.top
        }
        Image{
            id : imgAvatar
            height: 150
            width: 150
            source: "qrc:/images/select_avt.png"
            anchors.verticalCenterOffset: 0
            anchors.topMargin: 0
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: infoContainer.left
            fillMode: Image.PreserveAspectFit
            MouseArea{
                anchors.fill: parent
                onClicked: fileDialog.open()
            }
        }

        Item{
            id : infoContainer
            height: parent.height
            anchors.left: imgAvatar.right
            anchors.right: parent.right

            Column{
                id : leftContainer
                height: childrenRect.height
                width: parent.width/2 - 8
                anchors.left: parent.left
                anchors.leftMargin : 16
                anchors.verticalCenter: parent.verticalCenter
                spacing: 8

                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "Name : "
                        textField.text: ""
                        id : inputName
                    }

                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "Birthday : "
                        textField.text: ""
                        textField.placeholderText: "dd/mm/yyyy"
                        id : inputDob
                        textField.onFocusChanged: {
                            if(textField.focus){
                                if(textField.color == "red")
                                    textField.text = ""
                                resetTextField(inputDob)
                            }
                        }
                    }

                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "Address : "
                        textField.text: ""
                        id: inputAddress
                    }

                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "Phone : "
                        textField.text: ""
                        id : inputPhone
                        textField.onFocusChanged: {
                            if(textField.focus){
                                if(textField.color == "red")
                                    textField.text = ""
                                resetTextField(inputPhone)
                            }
                        }
                    }
            }

            Column{
                height: childrenRect.height
                width: (parent.width /2) - 32
                anchors.right: parent.right
                anchors.top: leftContainer.top
                spacing: 8
                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "User Name : "
                        textField.text: ""
                        id : inputUserName
                        textField.onFocusChanged: {
                            if(textField.focus){
                                if(textField.color == "red")
                                    textField.text = ""
                                resetTextField(inputUserName)
                            }
                        }
                    }

                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "Password : "
                        textField.text: ""
                        id : inputPassword
                        textField.onFocusChanged: {
                            if(textField.focus){
                                if(textField.color == "red")
                                    textField.text = ""
                                resetTextField(inputPassword)
                            }
                        }
                    }

                    FormText{
                        height: 36
                        fontSize: 16
                        width: parent.width
                        txtTitle: "Hire Date : "
                        textField.text: ""
                        textField.placeholderText: "dd/mm/yyyy"
                        id: inputHireDate
                        textField.onFocusChanged: {
                            if(textField.focus){
                                if(textField.color == "red")
                                    textField.text = ""
                                resetTextField(inputHireDate)
                            }
                        }
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

                var dob = inputDob.textField.text
                var phone = inputPhone.textField.text
                var hireDate = inputHireDate.textField.text
                var password = inputPassword.textField.text
                var userName = inputUserName.textField.text

                var isValidNewUser = true;
                if(!isValidDateFormat(dob)){
                    inputDob.textField.color = "red"
                    inputDob.textField.font.bold = true
                    isValidNewUser = false;
                    console.log("dob Invalid")
                }
                if(!isValidDateFormat(hireDate)){
                    inputHireDate.textField.color = "red"
                    inputHireDate.textField.font.bold = true
                    isValidNewUser = false;
                    console.log("hireDate Invalid")
                }
                if(!isValidVietnamesePhoneNumber(phone)){
                    inputPhone.textField.color = "red"
                    inputPhone.textField.font.bold = true
                    isValidNewUser = false;
                    console.log("phone Invalid")
                }
                if(!isValidPassword(password)){
                    inputPassword.textField.color = "red"
                    inputPassword.textField.font.bold = true
                    isValidNewUser = false;
                    console.log("password Invalid")
                }

                if(!userController.checkUserNameExisted(userName)){
                    inputUserName.textField.color = "red"
                    inputUserName.textField.font.bold = true
                    isValidNewUser = false;
                    console.log("userName Invalid")
                }

                if(!isValidNewUser){
                    console.log("Not valid Data");
                    return;
                }

                var name = inputName.textField.text
                var address = inputAddress.textField.text

                if(name.length == 0 || address.length == 0 || userName.length == 0){
                    console.log("Empty Value")
                    return;
                }

                var avatar = imgAvatar.source


                userController.addUser(name, dob, address, phone, userName,
                                       password, avatar, hireDate);
                forceSync()
                popupAddUser.close();
            }
        }

        ButtonDefault{
            width: ms.button_default.width_extra
            name : "Cancel"
            anchors.left: btnAdd.right
            anchors.leftMargin: 32
            anchors.verticalCenter: parent.verticalCenter
            onBtnClicked: {
                popupAddUser.close();
            }
        }
    }
}
