import QtQuick 2.0

Rectangle{
    id:botRect
    height: ms.progressbar.height
    radius: ms.progressbar.radius
    color: ms.color.gray
    property string pgColor: ms.color.state_accepted
    property int value : 0 // from 0 to 100
    property int time: 200

    onValueChanged: {
        if(value < 0) value = 0;
        if(value > 100) value = 100;
    }

    Rectangle{
        id : topRect
        height: ms.progressbar.height
        radius: ms.progressbar.radius
        color: pgColor
        width: ((value/100.0) * botRect.width ) + 2
        anchors.left: parent.left
        anchors.leftMargin: -1
        visible: value != 0
        z:1
        Behavior on width {
            PropertyAnimation{
                duration: time
                easing.type: Easing.Linear
            }
        }
    }
}




