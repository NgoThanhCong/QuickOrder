import QtQuick 2.0

Text{
    property int value : 0
    height: ms.item.height
    width: ms.item.width
    text: value + "%"
    font.pixelSize: ms.normalText.fontSize
    lineHeight: ms.titleText.fontSize
    font.weight: Font.DemiBold
    color: ms.color.black
    anchors.right: parent.right
    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignRight
    anchors.rightMargin: ms.margin.normal
}
