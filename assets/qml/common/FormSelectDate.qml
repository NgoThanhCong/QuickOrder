import QtQuick 2.0
import QtQuick.Controls 2.5

Item {
    property string txtTitle: ""
    property alias comboBox: _comboBox
    property int fontSize: 24

    Label {
        id: title
        text: qsTr(txtTitle)
        width: parent.width * 0.25
        height: parent.height
        font.family: "Noto Sans"
        font.pixelSize: fontSize
    }

    DropDownList{
        id : _comboBox
        height: title.height
        anchors.left: title.right
        anchors.leftMargin: 32
        anchors.right: parent.right
        anchors.top: title.top
        color: "black"
    }
}
