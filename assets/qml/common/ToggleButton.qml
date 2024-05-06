import QtQuick 2.0

Rectangle{
    height: 16
    width: 16
    radius: 6
    color: isEnable ? isChecked ? ms.color.primary : ms.color.white : "#EBEEF4"
    antialiasing: true
    border.width: 1
    border.color: ms.color.gray

    property bool isChecked: false
    property bool isEnable: true
    property string srcIco: "qrc:/icons/ic_check.png"



    Image{
        anchors.fill: parent
        source: isChecked ? srcIco : ""
    }

    MouseArea{
        anchors.fill: parent
        onClicked: isChecked = !isChecked
    }
}
