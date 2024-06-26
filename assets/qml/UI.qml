import QtQuick 2.12
import QtQuick.Dialogs 1.1
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "screens"

Rectangle{
    id: mainScreen
    anchors.fill: parent
    border.color: ms.color.stroke
    border.width: 1

    TitleBar{
        id : titleBar
        width: parent.width
        z:2
    }

    NavigationBar{
        id : navigationBar
        anchors.top: titleBar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        onSelectedIdx: screenViewer.currentIdx = idx
        onSettingsClicked: showSettingsPopup()
        visible: !loginScreen.visible && LoginScreenModel.isAdmin() // ẩn hiện
    }

    ScreenViewer{
        id : screenViewer
        currentIdx: 0
        anchors.top: titleBar.bottom
        anchors.left: navigationBar.right
        width: parent.width - navigationBar.width
        height: parent.height - titleBar.height
        visible: navigationBar.visible
    }

    OrderScreen{
        id : orderScreen
        anchors.top: titleBar.bottom
        height: parent.height - titleBar.height
        width: parent.width
        visible: !loginScreen.visible && !LoginScreenModel.isAdmin()
    }

    LoginScreen{
        id : loginScreen
        anchors.fill: parent
        visible: !LoginScreenModel.isLogin
    }

}
