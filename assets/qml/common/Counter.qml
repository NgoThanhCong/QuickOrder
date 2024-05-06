import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import "../common"

Rectangle {
    id : counter
    height: 30
    width: 120
    color: "transparent"
    radius: 15

    property int valueCounter : 0

    function inc(){
        if(valueCounter < 100){
            valueCounter +=1;
        }
    }

    function dec(){
        if(valueCounter > 0){
            valueCounter -=1;
        }
    }

    Row{
        spacing: 8
        height: 26
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter

        ImageBtnBg{
            width: 26
            height: 26
            onBtnClicked: dec()
            src : "qrc:/icons/ic_remove.png"
            btnColor:  "white"
            radius: 10
        }

        TextNormal{
            id : txtValue
            width: 26
            height: 26
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.weight: Font.Medium
            text: "(x" + valueCounter +")"
            font.pixelSize: 18
        }

        ImageBtnBg{
            width: 26
            height: 26
            src: "qrc:/icons/ic_add.png"
            btnColor: "white"
            onBtnClicked: inc()
            radius: 10
        }
    }
}
