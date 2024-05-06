import QtQuick 2.0
import "../common"

Item {
    height: 90
    width: parent.width
    property var dataOptions: [0,0,0]

    signal option1Selected();
    signal option2Selected();
    signal option3Selected();

    Row{
        anchors.top : parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins : 8

        CircleItem{
            height: parent.height
            width: parent.width/3
            title: "S"
            value: dataOptions[0]
            onBtnClicked: option1Selected()
        }

        CircleItem{
            height: parent.height
            width: parent.width/3
            title: "M"
            value: dataOptions[1]
            onBtnClicked: option2Selected()
        }

        CircleItem{
            height: parent.height
            width: parent.width/3
            title: "L"
            value: dataOptions[2]
            onBtnClicked: option3Selected()
        }

    }
}
