import QtQuick.Controls 2.12
import QtQuick.Dialogs 1.3
import QtQuick 2.0
import QtQml 2.3
import "../component"
import "../common"

PopupBase {
    id : basePopup
    height: 350
    width: 650

    signal forceSync()
    property bool isEditMode: false
    property var dataMenuItem: null

    onOpened: {
        if(isEditMode){
            popupTitle = "Edit Menu Item"
        }else{
            popupTitle = "Add New Menu Item"
        }

        if(dataMenuItem !== null){
            inputName.textField.text = dataMenuItem.name
            inputPriceS.textField.text = dataMenuItem.price
            inputPriceM.textField.text = dataMenuItem.priceM
            inputPriceL.textField.text = dataMenuItem.priceL
            inputCategory.cbBox.currentIndex = menuModel.getIdxByCatId(dataMenuItem.categoryId);
            itemImage.source = dataMenuItem.image
        }else{
            inputName.textField.text = ""
            inputPriceS.textField.text = ""
            inputPriceM.textField.text = ""
            inputPriceL.textField.text = ""
            inputCategory.cbBox.currentIndex = 0
            itemImage.source = "qrc:/images/default_item_img.jpg"
        }
    }

    function isDataUpdated(){
        return inputName.textField.text      !== dataMenuItem.name    ||
            inputPriceS.textField.text       !== dataMenuItem.price   ||
            inputPriceM.textField.text       !== dataMenuItem.priceM  ||
            inputPriceL.textField.text       !== dataMenuItem.priceL  ||
            inputCategory.cbBox.currentIndex !== menuModel.getIdxByCatId(dataMenuItem.categoryId);
    }

    FileDialog {
        id: fileDialog
        title: "Select an Image"
        folder: shortcuts.pictures
        nameFilters: ["Image files (*.png)"]
        onAccepted: {
            console.log("Image Selected: ", fileDialog.fileUrl)
            itemImage.source = fileDialog.fileUrl
        }
    }

    Item{
        id : content_popup
        height: parent.height - bottomBar.height - titleBar.height
        anchors{
            left: parent.left
            right: parent.right
            leftMargin: 32
            rightMargin: 32
            bottom: bottomBar.top
        }
        Image{
            id : itemImage
            height: 200
            width: 200
            source: "qrc:/images/default_item_img.jpg"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            fillMode: Image.PreserveAspectFit
            MouseArea{
                anchors.fill: parent
                onClicked: fileDialog.open()
            }
        }

        Column{
            id : leftContainer
            height: childrenRect.height
            anchors.left: itemImage.right
            anchors.right: parent.right
            anchors.leftMargin: 16
            anchors.verticalCenter: parent.verticalCenter
            spacing: 8

            FormText{
                height: 36
                fontSize: 16
                width: parent.width
                txtTitle: "Name : "
                textField.text: ""
                id : inputName
            }

            FormDropdownList{
                height: 36
                fontSize: 16
                width: parent.width
                txtTitle: "Category : "
                id: inputCategory
                cbBox.model: menuModel.getCats()
            }

            FormText{
                height: 36
                fontSize: 16
                width: parent.width
                txtTitle: "Size S : "
                textField.placeholderText: "0.00"
                id : inputPriceS
                textField.validator: DoubleValidator {bottom: 0.0; decimals: 2}
            }

            FormText{
                height: 36
                fontSize: 16
                width: parent.width
                txtTitle: "Size M : "
                textField.placeholderText: "0.00"
                id : inputPriceM
                textField.validator: DoubleValidator {bottom: 0.0; decimals: 2}
            }

            FormText{
                height: 36
                fontSize: 16
                width: parent.width
                txtTitle: "Size L : "
                textField.placeholderText: "0.00"
                id : inputPriceL
                textField.validator: DoubleValidator {bottom: 0.0; decimals: 2}
            }
        }
    }

    Item{
        id : bottomBar
        height: ms.Popup.bottom_bar_height
        width: childrenRect.width
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Rectangle{
            height: ms.Popup.div_width
            width: parent.width
            color: ms.color.stroke
            anchors.top: parent.top
        }

        ButtonDefault{
            id : btnAdd
            width: ms.button_default.width_extra
            name : "Ok"
            anchors.left: parent.left
            anchors.leftMargin: ms.margin.normal
            anchors.verticalCenter: parent.verticalCenter
            onBtnClicked: {
                forceActiveFocus()
                var name = inputName.textField.text
                var catIdx = inputCategory.cbBox.currentIndex
                var priceS = inputPriceS.textField.text
                var priceM = inputPriceM.textField.text
                var priceL = inputPriceL.textField.text
                var imgSrc = itemImage.source

                if(name.length == 0 || priceS.length === 0 || priceM.length === 0 || priceL === 0){
                    return;
                }
                if(isEditMode){
                    menuController.updateMenuItem(dataMenuItem.itemId, name, imgSrc, catIdx, priceS, priceM, priceL);
                }else{
                    menuController.addMenuItem(name, imgSrc, catIdx, priceS, priceM, priceL);
                }

                menuController.syncData()
                close();
            }
        }

        ButtonDefault{
            width: ms.button_default.width_extra
            name : "Cancel"
            anchors.left: btnAdd.right
            anchors.leftMargin: 32
            anchors.verticalCenter: parent.verticalCenter
            onBtnClicked: {
                close();
            }
        }
    }
}
