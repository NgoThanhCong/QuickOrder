import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import "../common"
import ".."

Popup{
    id :  popup_base
    height: 150
    width: 360
    anchors.centerIn: parent
    modal: true
    focus: true
    closePolicy: Popup.CloseOnEscape
    margins: 0
    padding: 0
    property string popupTitle: "Are you sure want to delete !"
    property alias titlePopup: _titlePopup
    property string confirmPopupData: ""

    signal discard();
    signal confirm(var data);

    background: Rectangle{
        anchors.fill: parent
        radius: ms.Windows.radius
        color: ms.color.white
    }

    Overlay.modal: Rectangle {
        color: Qt.rgba(0,0,0,0.5)
    }

    Item{
        height: ms.Popup.title_height
        width: parent.width
        TextTitle{
            id : _titlePopup
            anchors.left: parent.left
            anchors.leftMargin: ms.margin.normal
            text: popupTitle
            anchors.horizontalCenter: parent.horizontalCenter
            font.pixelSize: ms.Popup.title_pixelSize
            font.bold: true
            anchors.verticalCenter: parent.verticalCenter
            font.weight: Font.DemiBold
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }

    Item{
        id : bottomBar
        height: ms.Popup.bottom_bar_height
        width: parent.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Rectangle{
            height: ms.Popup.div_width
            width: popup_base.width
            color: ms.color.stroke
            anchors.top: parent.top
        }

        ButtonDefault{
            id : btnAdd
            width: ms.button_default.width_extra
            name : "Ok"
            anchors.left: parent.left
            anchors.leftMargin: 40
            anchors.verticalCenter: parent.verticalCenter
            onBtnClicked: {
                forceActiveFocus()
                confirm(confirmPopupData)
                close()
            }
        }

        ButtonDefault{
            width: ms.button_default.width_extra
            name : "Cancel"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 40
            onBtnClicked: {
                discard()
                close();
            }
        }
    }
}
