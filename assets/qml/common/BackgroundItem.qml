import QtQuick 2.0

Rectangle{
    height: ms.item.height
    color: ms.color.white
    anchors.left: parent.left
    anchors.right: parent.right
    anchors.leftMargin: 1

    Divider {
        id: borderBottom
        anchors.rightMargin:-border.width
        anchors.topMargin:  -border.width
        anchors.leftMargin: -border.width
    }
}

