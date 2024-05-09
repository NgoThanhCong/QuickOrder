import QtQuick 2.0
import "common"

Item {
    height: ms.TitleBar.height
    width: ms.TitleBar.width
    property string version: TitleBarModel.version
    property var settingsModel: SettingsScreenModel

    ImageButton{
        id : btnClose
        src: "qrc:/icons/ic_close.png"
        onBtnClicked: {
            app.close();
        }
        anchors.right: parent.right
        btnColor: loginScreen.visible ? "white" : "black"
    }

    ImageButton{
        id : btnLogout
        anchors.right: btnClose.left
        src : "qrc:/icons/ic_logout.png"
        btnColor: loginScreen.visible ? "white" : "black"
        visible: LoginScreenModel.isLogin
        onBtnClicked: LoginScreenController.logout()
    }

    ImageButton{
        id : btnExport
        anchors.right: btnLogout.left
        icHeight: 24
        icWidth: 24
        src : "qrc:/icons/ic_export.png"
        btnColor: loginScreen.visible ? "white" : "black"
        visible: LoginScreenModel.isLogin && !LoginScreenModel.isAdmin()
        onBtnClicked: ReportScreenController.exportData(0);
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

