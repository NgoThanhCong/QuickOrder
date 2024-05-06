import QtQuick 2.0
import QtGraphicalEffects 1.0

Item{

    Rectangle{
        anchors.fill: parent
        color: "white"
        id: bg
        radius: 10
    }

    DropShadow {
        anchors.fill: bg
        horizontalOffset: 1
        verticalOffset: 1
        radius: 3
        samples: 6
        color: "#60000000"
        source: bg
    }
}
