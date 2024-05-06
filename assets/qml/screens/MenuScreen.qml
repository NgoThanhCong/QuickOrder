import QtQuick 2.12
import "../common"
import "../component"
import "../popup"

Rectangle{

    property var menuController: MenuScreenController
    property var menuModel: MenuScreenModel
    color: "#F9F9F9"

    TextTitle{
        id : titleCategory
        anchors{
            top: parent.top
            left: parent.left
            right: parent.right
            margins : 8
        }
        text: "Category"
        font.pixelSize: 24
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width
        height: 40
    }

    AddCategoryPopup{
        id : addCategoryPopup
    }

    ConfirmationPopup{
        width: 680
        id : removeCatConfirmationPopup
        popupTitle: "All Menu Item unders this Category will be deleted !"
        titlePopup.color: "red"
        onConfirm: {
            menuController.removeCat(data)
            menuController.syncData()
        }
    }

    GridView{
        id : catGridView
        height: 100
        width: parent.width
        anchors{
            top: titleCategory.bottom
            left: parent.left
            right: parent.right
            margins: 8
        }
        interactive: false
        model: menuModel.cats
        cellHeight : 42
        cellWidth : 150
        header: Item {
            height: 42
            width: 150
            ButtonDefault{
                name : "Add Category"
                height: 36
                width: 120
                anchors{
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }

                onBtnClicked: {
                    addCategoryPopup.isEditing = false;
                    addCategoryPopup.catObj = null;
                    addCategoryPopup.open()
                }
            }
        }

        delegate: CategoryCard{
            onCategoryEdit: {
                console.log(cat.name)
                addCategoryPopup.isEditing = true;
                addCategoryPopup.catObj = cat
                addCategoryPopup.open()
            }
        }
    }

    TextTitle{
        id : titleMenuItem
        anchors{
            top: catGridView.bottom
            left: parent.left
            right: parent.right
            margins : 8
        }
        text: "Menu Item"
        font.pixelSize: 24
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        width: parent.width
        height: 40
    }

    Item {
        id : header
        height: 48
        width: menuItemLv.width
        anchors.top: titleMenuItem.bottom
        anchors.topMargin: 8

        Row{
            anchors.fill: parent
            anchors.left: parent.left
            anchors.leftMargin: 20
            spacing: 8

            TagInfo{
                width: 80
                textContent: "Avatar"
                isHeader: true
            }

            TagInfo{
                width: 320
                textContent: "Name"
                isHeader: true
            }

            TagInfo{
                textContent: ""
                isHeader: true
            }

            TagInfo{
                textContent: "Category"
                isHeader: true
            }

            TagInfo{
                textContent: "Size S"
                width: 120
                isHeader: true
            }

            TagInfo{
                textContent: "Size M"
                width: 120
                isHeader: true
            }

            TagInfo{
                textContent: "Size L"
                width: 120
                isHeader: true
            }

            Item {
                height: parent.height
                width: parent.width / 4
            }


            Item {
                height: 50
                width: 150
                ButtonDefault{
                    name : "Add Menu Item"
                    height: 36
                    width: 120
                    anchors.centerIn: parent
                    onBtnClicked: {
                        addMenuItemPopup.dataMenuItem = null
                        addMenuItemPopup.isEditMode = false
                        addMenuItemPopup.open()
                    }
                }
            }
        }
    }

    AddMenuItemPopup{
        id : addMenuItemPopup
    }

    ListView{
        id : menuItemLv
        clip: true
        spacing: 0
        anchors{
            left: parent.left
            right: parent.right
            top: header.bottom
            bottom: parent.bottom
            margins: 8
        }
        model : menuModel.menuItems

        delegate: MenuItemCard{

        }
    }

    ConfirmationPopup{
        id : confirmRemoveMenuItemPopup
        onConfirm: {
            menuController.removeMenuItem(confirmPopupData)
            menuController.syncData()
        }
    }
}
