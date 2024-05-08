import QtQuick 2.12
import QtQuick.Dialogs 1.1
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQml 2.3

import '../measurement/ms_1368x768.js' as Measurement_1368x768

ApplicationWindow {
    id: app
    height: ms.Windows.height
    width: ms.Windows.width
    flags: Qt.Window | Qt.FramelessWindowHint
    property var ms: Measurement_1368x768
    color: ms.color.white

    Rectangle{
        anchors.fill: parent
        color: 'white'
        id : bgRect
    }

    DropShadow {
      anchors.fill: bgRect
      horizontalOffset: 1
      verticalOffset: 1
      radius: 10
      samples: 10
      source: bgRect
      color: "black"
      Behavior on radius { PropertyAnimation { duration: 100 } }
    }

    Loader {
        id: loader
        asynchronous: true
        anchors.fill: parent
        sourceComponent: UI {
            anchors.fill: parent
            Component.onCompleted: {
                app.showNormal()
            }
        }
    }

}
