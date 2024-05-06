import QtQuick 2.0

Rectangle {
   height: ms.icon.height
   width: ms.state_percent.width
   property int value: 0
   property int percent: 0
   property alias passed: txtLed.passed

   TextLed
   {
       id : txtLed
       anchors.left: parent.left
       anchors.leftMargin: ms.margin.normal
       anchors.verticalCenter: parent.verticalCenter
   }

   TextNormal{
       height: ms.normalText.lineHeight
       width: ms.state_percent.item_width
       id : txtQuantity
       text: value
       anchors.verticalCenter: parent.verticalCenter
       horizontalAlignment: Text.AlignRight
       anchors.right: txtPercent.left
       anchors.rightMargin: ms.margin.short
   }

   TextPercent{
       id : txtPercent
       height: ms.normalText.lineHeight
       width: ms.state_percent.item_width
       value: percent
       anchors.verticalCenter: parent.verticalCenter
   }

}
