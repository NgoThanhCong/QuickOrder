import QtQuick 2.0
import "../common"
import "../popup"

Rectangle{
    height: 40
    width: 145
    border.color: focus ? ms.color.primary : ms.color.gray;
    radius: ms.form_text_field.radius
    antialiasing: true
    signal categoryEdit(var cat)

    TextSubTitle{
        id: cateName
        text: modelData.name
        height: parent.height
        anchors{
            left: parent.left
            right: btnEdit.left
            margins: 4
        }
        horizontalAlignment: Text.AlignHCenter
    }

    ImageButton{
        id : btnEdit
        src: "qrc:/icons/ic_edit.png"
        width: 30
        height: 30
        anchors{
            right: btnClose.left
        }

        onBtnClicked: {
            categoryEdit(modelData)
        }
        anchors.verticalCenter: parent.verticalCenter
        btnColor: "black"
        visible: modelData.categoryId !== 7
        z:10
    }

    ImageButton{
        id : btnClose
        src: "qrc:/icons/ic_close.png"
        width: 30
        height: 30
        anchors{
            right: parent.right
        }
        visible: modelData.categoryId !== 7

        onBtnClicked: {
            removeCatConfirmationPopup.confirmPopupData = modelData.categoryId
            removeCatConfirmationPopup.open()
        }
        anchors.verticalCenter: parent.verticalCenter
        btnColor: "black"
        z:10
    }
}
