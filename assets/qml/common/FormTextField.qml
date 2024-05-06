import QtQuick 2.9

Rectangle {
    id : imgBtn
    height: ms.form_text_field.height
    width: ms.form_text_field.width
    radius: ms.form_text_field.radius
    antialiasing: true
    border.color: _textField.focus ? ms.color.primary : ms.color.gray
    signal enterPressed()

    property string title: ""
    property alias textField: _textField
    property string textValue: ""

    Column{
        height: ms.form_text_field.column_height
        anchors{
            verticalCenter: parent.verticalCenter
            left: parent.left
            right: parent.right
            leftMargin: ms.margin.normal
            rightMargin: ms.margin.normal
        }

        TextNormal{
            text: title
            color: Qt.rgba(37/255, 37/255, 37/255, 0.80)
            height: lineHeight
        }

        TextInput{
            id : _textField
            height: 30
            width: parent.width
            color: ms.color.gray
            font.weight: Font.Normal
            font.pixelSize: ms.subTitleText.fontSize
            font.family: "Noto Sans"
            onTextChanged: textValue = text
            onAccepted: enterPressed()
            padding: {
                leftPadding : 0
                topPadding: 0
                rightPadding : 0
                bottomPadding : 0
            }
        }
    }
}
