import QtQuick 2.12
import "../component"
import "../common"
import "../popup"
import QtQml 2.3

Rectangle{
    id : root
    property var userController: UserScreenController
    property var userModel: UserScreenModel
    color: "#F9F9F9"

    TextTitle{
        id : titleUser
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            margins : 8
        }
        text: "User Manager"
        font.pixelSize: 24
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width
        height: 40
    }


    Item {
        id : btnAdd
        height: 50
        width: 150
        anchors.right: parent.right
        anchors.top: titleUser.bottom
        ButtonDefault{
            name : "Add User"
            height: 36
            width: 120
            anchors.centerIn: parent
            onBtnClicked: {
                popupAddUser.open()
            }
        }
    }

    ConfirmationPopup{
        id : confirmationPopup
        onConfirm: {
            console.log("Remove User:", confirmPopupData)
            userController.removeUser(confirmPopupData)
            userController.syncData()
        }
    }

    UpdatePasswordPopup{
        id : updatePasswordPopup

    }

    ListView{
        id : listUsers
        model : userModel.users
        spacing: 8
        clip:true
        anchors{
            left: parent.left
            right: parent.right
            top: btnAdd.bottom
            bottom: parent.bottom
            margins: 10
        }
        delegate: UserCard{
            width: parent.width
        }
        snapMode: ListView.SnapToItem
    }

    AddUserPopup{
        id : popupAddUser
        onForceSync: userController.syncData()
    }

    Component.onCompleted: {
        console.log("User Screen")
    }

}
