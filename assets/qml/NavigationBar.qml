import QtQuick 2.0
import QtQuick.Controls 2.1
import "common"
import "component"

Item {
    height: ms.NavigationBar.height
    width:  ms.NavigationBar.width
    signal selectedIdx(var idx)
    signal settingsClicked()
    property bool isPopupMode: false
    property var data_model: NavigationBarModel.items
    clip:true

    ListView{
        id : itemList
        width: parent.width
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: isPopupMode ? 0 : ms.margin.normal
        interactive: isPopupMode
        model: data_model.length
        ScrollBar.vertical: ScrollBar{
            active: true
            width: ms.progressbar.height
        }
        snapMode: ListView.SnapToItem
        delegate: Item_Navi{
            width: isPopupMode ? ms.icon.width_popup : ms.icon.width
            icSrc: data_model[index].src
            title: data_model[index].name
            enable: data_model[index].isEnable
            onItemClicked: {
                itemList.currentIndex = index
                selectedIdx(index)
            }

            isHighlight: itemList.currentIndex == index
        }
    }

    Divider {
        id: borderBottom
        anchors.leftMargin : -border.width
        anchors.topMargin:  -border.width
        anchors.bottomMargin: -border.width
        visible: !isPopupMode
    }
}
