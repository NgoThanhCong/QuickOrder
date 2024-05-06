import QtQuick 2.0
import "common"

Item {
    height: 64
    width: parent.width
    property string version: TitleBarModel.version
    property string appName: TitleBarModel.appName

    // Title Bar with moving Window feature.
    Item{
        width: parent.width
        height: 64
        anchors.top: parent.top
        z:-1

        MouseArea{
            anchors.fill: parent
            property var cur_pos: ({})
            onEntered: cur_pos = [mouseX,mouseY]
            onPositionChanged: {
                app.x += (mouse.x - cur_pos[0])
                app.y += (mouse.y - cur_pos[1])
            }
        }
    }

    ImageButton{
        id : btnClose
        src: "qrc:/icons/ic_close.svg"
        onBtnClicked: {
            app.close();
        }
        anchors.right: parent.right
    }

    ImageButton{
        id: btnNormal
        src: "qrc:/icons/ic_maximize.svg"
        onBtnClicked: {
            print("Show Maximized")
            app.changeSize()
        }
        anchors.right: btnClose.left
    }

    ImageButton{
        id: btnMinimize
        src: "qrc:/icons/ic_minimize.svg"
        onBtnClicked: {
            print("Show Minimzed")
            app.showMinimized();
        }
        anchors.right: btnNormal.left
    }


    Image {
        id: imgLogo
        source: "qrc:/icons/img_logo.svg"
        height: 24
        width: 174
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.topMargin: 20
    }

    Text{
        id :txtVersion
        text: "Version: " + version
        font.pixelSize: 12
        lineHeight: 16.43
        color: "#778A96"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 27
        anchors.leftMargin: 206
    }

    Text{
        id: txtAppName
        text: appName
        lineHeight: 27.24
        font.pixelSize: 20
        horizontalAlignment: Text.AlignHCenter
        height: 27
        width: 450
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.centerIn: parent
        color: "#252525"
        font.bold: true
    }


    Divider {
        id: borderBottom
        anchors.leftMargin : -border.width
        anchors.rightMargin: -border.width
        anchors.topMargin:  -border.width
    }
}

