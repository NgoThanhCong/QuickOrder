import QtQuick 2.0

Text{
    width: parent.width
    lineHeight: ms.titleText.lineHeight
    height: ms.titleText.lineHeight
    color: ms.color.black
    font.pixelSize: ms.titleText.fontSize
    anchors.rightMargin: ms.margin.short
    anchors.leftMargin: ms.margin.normal
    font.weight: Font.DemiBold
}

