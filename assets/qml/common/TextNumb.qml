import QtQuick 2.0

Text{
    height: ms.item.height
    font.pixelSize: ms.normalText.fontSize
    lineHeight: ms.normalText.lineHeight
    font.weight: Font.DemiBold
    color: ms.color.black
    anchors.right: parent.right
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignRight
    anchors.rightMargin: ms.margin.normal
}
