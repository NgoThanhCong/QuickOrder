import QtQuick 2.9
import QtQuick.Controls 2.5

Item {
    property string txtTitle: ""
    property alias cbBox: _cbBox
    property int fontSize: 24
    property bool formDisable: false
    antialiasing: true
    signal enterPressed(var text)

    TextTitle {
        id: title
        text: qsTr(txtTitle)
        width: parent.width * 0.25
        height: parent.height
        font.family: "Noto Sans"
        font.pixelSize: fontSize
    }

    Rectangle {
        height: title.height
        anchors.left: title.right
        anchors.right: parent.right
        anchors.leftMargin: 32
        anchors.rightMargin: 8
        radius: ms.form_text_field.radius
        antialiasing: true
        border.color:{
            if (formDisable) return "transparent"
            else return  _cbBox.focus ? ms.color.primary : ms.color.gray;
        }
        color: formDisable ? Qt.rgba(0, 0, 0, 0.2) : "white"

        Column{
            anchors{
                top: parent.top
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: 2
            }

            ComboBox{
                id : _cbBox
                height: parent.height
                width: parent.width
                font.weight: Font.Normal
                font.pixelSize: fontSize
                font.family: "Noto Sans"                
                background: Item{}
                padding: {
                    leftPadding : 0
                    topPadding: 0
                    rightPadding : 0
                    bottomPadding : 0
                }
            }
        }
    }
}
