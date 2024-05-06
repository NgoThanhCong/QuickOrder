import QtQuick 2.0

Item {
    height: 57
    width: 160
    property string textTitle: "Name"
    property string textContent: "Bubble Brown Sugar Fresh Milk"
    anchors.verticalCenter: parent.verticalCenter
    property bool isHeader: false

    TextNormal{
        text: textContent
        font.pixelSize: 18
        height: 50
        width: parent.width
        anchors.bottom: parent.bottom
        verticalAlignment: Text.AlignVCenter
        color: isHeader ? "#696969" :"#2C2C2C"
        font.bold: isHeader
    }
}
