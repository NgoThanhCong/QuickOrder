import QtQuick 2.0

Rectangle {
    id : icBtn
    width: 71
    height: 28
    radius: 9
    border.width: 1
    border.color: isSelected ? "#004AAD" : ms.color.stroke
    property bool isPassed: false
    property bool isSelected: false
    signal btnClicked()
    onIsSelectedChanged: {
        if(isSelected) txtLed.text.color = "#004AAD"
        else txtLed.text.color = isPassed ? txtLed.passedColor : txtLed.failedColor
    }

    TextLed{        
        id : txtLed
        passedContent: "Pass"
        failedContent: "Fail"
        height: 28
        width: isPassed ? 40 : 32
        anchors.centerIn: parent
        passed: isPassed
        text.horizontalAlignment: Text.AlignHCenter
        text.verticalAlignment: Text.AlignVCenter
    }

    PropertyAnimation {
        id: scaleDownAnim
        targets: [icBtn]
        properties: "scale"
        from: 1.0
        to: 0.9
        duration: 100
    }

    PropertyAnimation {
        id: scaleUpAnim
        targets: [icBtn]
        properties: "scale"
        from: 0.9
        to: 1.0
        duration: 100
    }

    MouseArea{
        z:1
        anchors.fill: parent
        onEntered: scaleDownAnim.restart()
        onReleased: scaleUpAnim.restart()
        onClicked: btnClicked()
    }
}
