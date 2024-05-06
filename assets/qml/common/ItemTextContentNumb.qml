import QtQuick 2.0

Item {
    anchors.left: parent.left
    anchors.right: parent.right
    property string title: ""
    property string numb: ""
    anchors.leftMargin: 0

    TextNormal{        
        text: title
        height: parent.height
        anchors.right: txtNumb.left
        anchors.left: parent.left
        anchors.leftMargin: ms.margin.normal
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
        font.pixelSize: 22
        font.bold: true
        font.weight: Font.Bold
        font.family: "Noto Sans"
    }

    TextNumb{
        id : txtNumb
        text: numb
        font.pixelSize: 22
        font.family: "Noto Sans"
    }
}
