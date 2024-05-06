import QtQuick 2.0
import "common"
import "component"

Item {
    height: 704
    width: 64
    signal selectedIdx(var idx)

    Component.onCompleted :{
        print(NavigationBarModel.items)
    }

    ListView{
        id : itemList
        width: parent.width
        height: 512
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 16
        interactive: false
        model: NavigationBarModel.items.length
        delegate: Item_Navi{
            icSrc: NavigationBarModel.items[index].src
            title: NavigationBarModel.items[index].name
            enable: NavigationBarModel.items[index].isEnable
            onItemClicked: {
                itemList.currentIndex = index
                selectedIdx(index)
            }

            isHighlight: itemList.currentIndex == index
        }
    }

    ListModel {
        id: naviModel

        ListElement {
            name: "Main"
            src:"qrc:/icons/ic_home.svg"
            isEnable : true
        }
        ListElement {
            name: "Cloud"
            src:"qrc:/icons/ic_cloud.svg"
            isEnable : true
        }
        ListElement {
            name: "Report"
            src:"qrc:/icons/ic_report.svg"
            isEnable : true
        }
    }

    ImageTextButton{
        id : inspectBtn
        src : "qrc:/icons/ic_inspection.svg"
        btnName :"Inspect"
        onBtnClicked: {
            print("Inspection Btn Clicked");
        }
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 24
    }


    Divider {
        id: borderBottom
        anchors.leftMargin : -border.width
        anchors.topMargin:  -border.width
        anchors.bottomMargin: -border.width
    }
}
