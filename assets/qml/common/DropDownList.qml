import QtQuick 2.12
import QtQuick.Controls 2.5
import QtGraphicalEffects 1.0
import "../common"

Rectangle{
    height: ms.dropdownlist.height
    width: ms.dropdownlist.width
    color: "#E7EBEF"
    radius: ms.dropdownlist.radius
    id : root
    property bool isShown: false
    property alias selection : currentSelection.text
    property var dataModel: null
    visible: dataModel.length !== 0

    ImageButton{
        id : icon
        height: ms.icon.height_ic
        width: height
        src : isShown ? "qrc:/icons/ic_arrow_up.png" : "qrc:/icons/ic_arrow_down.png"
        anchors.right: parent.right
        anchors.rightMargin: ms.dropdownlist.margin
        anchors.verticalCenter: parent.verticalCenter
        onBtnClicked: isShown = !isShown
    }

    TextNormal{
        id :currentSelection
        anchors.left: parent.left
        anchors.leftMargin: ms.dropdownlist.current_selection.margin_left
        anchors.right: icon.left
        anchors.rightMargin: ms.dropdownlist.current_selection.margin_right
        height: ms.dropdownlist.current_selection.height
        anchors.verticalCenter:  parent.verticalCenter
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft
    }

    MouseArea {
        anchors.fill: parent
        onClicked: isShown = !isShown
    }

    Rectangle{
        id : bgComboBox
        height: ms.dropdownlist.item.height
        visible: isShown
        width: parent.width
        radius: ms.dropdownlist.radius
        border.width: ms.margin.margin_1
        border.color: ms.color.stroke
        anchors.top: parent.bottom
        anchors.topMargin: ms.margin.extra_short

        ListView{
            id : cbList
            model: dataModel
            anchors.fill: parent
            clip: true
            onCurrentIndexChanged: currentSelection.text = dataModel[currentIndex]
            delegate:Rectangle{
                width: ms.dropdownlist.item.height
                height: ms.dropdownlist.item.height_cell
                color: "transparent"
                TextNormal{
                    id : txtItem
                    height: ms.dropdownlist.item.height_cell
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: ms.dropdownlist.item.margin_cell
                    anchors.rightMargin: ms.dropdownlist.item.margin_cell
                    anchors.verticalCenter:  parent.verticalCenter
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignLeft
                    color : cbList.currentIndex === model.index ? "#004AAD" : "#CC252525"
                    text: modelData
                }
                MouseArea{
                    width: bgComboBox.width
                    height: parent.height
                    onClicked: {
                        cbList.currentIndex = model.index
                        isShown = false
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {
                active: true
            }
        }
    }
}
