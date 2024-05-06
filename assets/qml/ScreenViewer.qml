import QtQuick 2.12
import QtQuick.Controls 2.12
import "screens"

Rectangle {
    property int currentIdx: 0
    color: ms.color.white

    SwipeView{
        currentIndex: currentIdx
        id : container
        anchors.fill: parent
        interactive: false
        orientation: Qt.Vertical
        clip:true

        UserScreen{
            height: ms.MainScreen.height
            width: ms.MainScreen.width
        }

        MenuScreen{
            height: ms.MainScreen.height
            width: ms.MainScreen.width
        }

        ReportScreen{
            height: ms.MainScreen.height
            width: ms.MainScreen.width
        }

        VoucherScreen{
            height: ms.MainScreen.height
            width: ms.MainScreen.width
        }

        SettingsScreen{
            height: ms.MainScreen.height
            width: ms.MainScreen.width
        }
    }

}
