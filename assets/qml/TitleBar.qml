import QtQuick 2.0
import "common"

Item {
    height: ms.TitleBar.height
    width: ms.TitleBar.width
    property string version: TitleBarModel.version
    property var settingsModel: SettingsScreenModel

    // Title Bar with moving Window feature.
    Item{
        width: parent.width
        height: ms.TitleBar.height
        anchors.top: parent.top
        z:-1
    }

    ImageButton{
        id : btnClose
        src: "qrc:/icons/ic_close.png"
        onBtnClicked: {
            app.close();
        }
        anchors.right: parent.right
        btnColor: loginScreen.visible ? "white" : "black"
    }

    // ImageButton{
    //     id: btnMinimize
    //     src: "qrc:/icons/ic_minimize.png"
    //     onBtnClicked: {
    //         print("Show Minimzed")
    //         app.showMinimized();
    //     }
    //     anchors.right: btnClose.left
    //     btnColor: loginScreen.visible ? "white" : "black"
    // }

    ImageButton{
        id : btnLogout
        anchors.right: btnClose.left
        src : "qrc:/icons/ic_logout.png"
        btnColor: loginScreen.visible ? "white" : "black"
        visible: LoginScreenModel.isLogin
        onBtnClicked: LoginScreenController.logout()
    }

    Image {
        id: imgLogo
        source: "qrc:/images/logo_horizontal.png"
        height: parent.height * 0.5
        fillMode: Image.PreserveAspectFit
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: ms.TitleBar.logo.margin
        anchors.topMargin: ms.TitleBar.logo.margin
        smooth: true
        antialiasing: true
    }

    Text{
        id: txtAppName
        text: settingsModel.storeName
        lineHeight: ms.TitleBar.appName.lineHeight
        font.pixelSize: ms.TitleBar.appName.fontSize
        horizontalAlignment: Text.AlignHCenter
        height: ms.TitleBar.appName.height
        width: ms.TitleBar.appName.width
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.centerIn: parent
        color: ms.color.primary
        font.bold: true
        visible: !loginScreen.visible
    }


    Divider {
        id: borderBottom
        anchors.leftMargin : -border.width
        anchors.rightMargin: -border.width
        anchors.topMargin:  -border.width
        visible: !loginScreen.visible
    }
}

