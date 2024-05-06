import QtQuick 2.6
import QtGraphicalEffects 1.2

Rectangle {
    property alias source: _image.source

    radius: 5
    color: "transparent"
    Image {
        id: _image
        smooth: true
        visible: false
        anchors.fill: parent
        source: img_src
        sourceSize: Qt.size(parent.size, parent.size)
        antialiasing: true
        fillMode: Image.PreserveAspectCrop
    }
    Rectangle {
        id: _mask
        color: "black"
        anchors.fill: parent
        radius: parent.radius
        visible: false
        antialiasing: true
        smooth: true
    }
    OpacityMask {
        id: mask_image
        anchors.fill: _image
        source: _image
        maskSource: _mask
        visible: true
        antialiasing: true
    }
}
