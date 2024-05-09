import QtQuick 2.12
import "../common"
import "../component"
import "../popup"
import QtGraphicalEffects 1.0
import QtQml 2.3

Rectangle {
    id : orderScreenRoot
    property var menuController: MenuScreenController
    property var menuModel: MenuScreenModel
    property var orderController: OrderScreenController
    property var orderModel: OrderScreenModel
    property var settingsModel: SettingsScreenModel
    property var reportModel: ReportScreenModel
    property var voucherModel: VoucherScreenModel
    property alias currentItemIdx: listOrderItem.currentIndex

    color: "#F9F9F9"

    Connections{
        target: LoginScreenModel
        onIsLoginChanged :{
            if(!LoginScreenModel.isLogin && LoginScreenModel.isAdmin()){
                orderController.clearOrder();
            }
        }
    }

    CheckoutConfirmPopup{
        id : checkoutConfirmPopup        
        onConfirm: {
            orderController.checkout(LoginScreenModel.currentUser);
            listOrderItem.currentIndex = -1
        }
    }

    InputVoucherPopup{
        id : voucherPopup
    }

    TextTitle{
        id : welcomeTxt
        height: 60
        width: 400
        color: "black"
        text: "Welcome to " + "<font color='#004AAD'>"+settingsModel.storeName+"</font>"
        font.pixelSize: 36
        font.bold: true
        font.weight: Font.ExtraBold

        anchors{
            top: parent.top
            left: parent.left
            topMargin: 16
            leftMargin: 32
        }
    }

    ListView{
        id : bestSellerLv
        anchors{
            top: parent.top
            bottom: menuItemLv.top
            right: paymentContainer.left
            margins: 16
        }
        width: parent.width/3
        enabled: false
        delegate: Item{
            height: bsBg.height/4
            width: parent.width
            TextTitle{
                id : txt
                height: parent.height
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: modelData
                color: ms.color.primary
                font.bold: true
                font.pixelSize: 26 - (index * 4)
            }

            DropShadow {
                anchors.fill: txt
                horizontalOffset: 1
                verticalOffset: 1
                radius: 3
                samples: 6
                color: "#60000000"
                source: txt
            }
        }

        Image {
            id : bsBg
            anchors.fill: parent
            source: "qrc:/images/img_bestseller.png"
            fillMode: Image.PreserveAspectFit
            z:-1
        }

        Component.onCompleted: {
            let data = [];
            for(var i=0;i<4;i++){
                data.push(reportModel.bestSellerItems[i].itemName);
            }
            bestSellerLv.model = data
        }
    }

    ListView {
        id : catLv
        height: 90
        orientation: Qt.Horizontal
        spacing: 32
        clip: true
        interactive: false
        anchors{
            top: welcomeTxt.bottom
            topMargin: 30
            left: parent.left
            right: paymentContainer.left
            leftMargin: 32
            rightMargin: 32
        }

        model : menuModel.cats
        property int idxSelected: -1

        delegate: CatItem{
            onBtnClicked: {
                menuModel.filterKey = catId
            }
            isSelected: index == catLv.idxSelected            
        }
    }

    TextTitle{
        id : menuItemTxt
        height: 60
        width: 400
        color: "black"
        text: "Menu Item"
        font.pixelSize: 32
        font.bold: true
        font.weight: Font.ExtraBold

        anchors{
            top: catLv.bottom
            left: parent.left
            topMargin: 16
            leftMargin: 32
        }
    }

    GridView {
        id : menuItemLv
        anchors{
            top: menuItemTxt.bottom
            bottom: parent.bottom
            left: parent.left
            leftMargin: 32
            right: paymentContainer.left
            margins: 8
        }
        clip: true
        cellHeight: 430
        cellWidth: 330
        model : menuModel.filtedItems
        delegate: MenuItem{

        }
    }

    Rectangle{
        id : paymentContainer
        height: parent.height
        width: 560
        anchors.right: parent.right
        color: "#FDFDFD"

        Item{
            id : staffInfo
            height: 80
            width: parent.width

            Rectangle{
                id : bg
                anchors.fill: parent
            }

            DropShadow {
                anchors.fill: bg
                horizontalOffset: 1
                verticalOffset: 1
                radius: 8
                samples: 17
                color: "#60000000"
                source: bg
            }

            CircularImage{
                id : avt
                height: 72
                width: 72
                radius: 72
                source : LoginScreenModel.currentUser.avatar
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 32

                Rectangle{
                    anchors.fill: parent
                    color: "transparent"
                    border.color: ms.color.stroke
                    border.width: 1
                    radius: height
                }
            }

            TextNormal {
                id : roleTxt
                height: avt.height/3
                anchors{
                    left: avt.right
                    right:parent.right
                    top: avt.top
                    margins: 4
                    leftMargin: 32
                }
                font.pixelSize: 18
                text: "Staff"
            }

            TextTitle{
                anchors{
                    top: roleTxt.bottom
                    right : parent.right
                    left: avt.right
                    leftMargin: 32
                    topMargin: 0
                    margins: 4
                }
                font.pixelSize: 22
                text : LoginScreenModel.currentUser.name
            }

            TextNumb{
                id : timeTxt
                text : TimeManager.currentDateTime
                anchors.top: parent.top
                anchors.right: parent.right
                font.pixelSize: 18
                font.bold: true
            }

            Image{
                id : icon
                source: orderModel.printerStatusSrc
                smooth: true
                antialiasing: true
                height: 32
                width: 32
                anchors {
                    top: timeTxt.bottom
                    right: parent.right
                    rightMargin: 16
                }
            }
        }

        Item{
            id : billInfo
            z:2
            anchors{
                top : staffInfo.bottom
                bottom : parent.bottom
                right : parent.right
                left : parent.left
            }

            TextTitle{
                id : billTitle
                height: 32
                anchors{
                    top: parent.top
                    left: parent.left
                    leftMargin: 32
                    topMargin: 16
                    margins: 4
                }
                font.pixelSize: 28
                font.bold: true
                text : "Bills"
            }

            ListView{
                id : listOrderItem
                anchors{
                    top: billTitle.bottom
                    bottom: totalInfo.top
                    margins : 16
                }
                width: parent.width
                model : orderModel.orderDataView
                snapMode: ListView.SnapToItem
                currentIndex: -1
                onCurrentIndexChanged :{
                    console.log(currentIndex);
                }

                delegate: Item{
                    height: isTopping ? toppingItem.height : orderItem.height
                    width: parent.width

                    OrderItem{
                        id : orderItem
                        anchors.fill: parent
                        visible: !isTopping
                    }

                    ToppingItem{
                        id : toppingItem
                        anchors.fill: parent
                        visible: isTopping
                    }
                }

                clip :true
            }

            Item{
                id : totalInfo
                height: 360
                width: parent.width
                anchors{
                    bottom: parent.bottom
                }

                ItemTextContentNumb{
                    id : subTotalTxt
                    anchors{
                        top: parent.top
                        topMargin: 8
                    }

                    height: 32
                    width: parent.width
                    title : "Subtotal"
                    numb: orderModel.subTotal
                }

                ItemTextContentNumb{
                    id : discountTxt
                    anchors{
                        top: subTotalTxt.bottom
                        topMargin: 16
                    }

                    height: 32
                    width: parent.width
                    title : "Discount"
                    numb: "<font color='#004AAD'>(" + orderModel.discountPercent + "%) </font>" + orderModel.discount

                    ImageButton{
                        id : btnAddVouncher
                        src : "qrc:/icons/ic_add.png"
                        btnColor: ms.color.primary
                        anchors.centerIn: parent
                        onBtnClicked: voucherPopup.open()

                        Rectangle{
                            height: 32
                            width: 32
                            anchors.centerIn: parent
                            color: "transparent"
                            radius: 50
                            border.width: 1
                            border.color: ms.color.primary
                        }
                    }
                }

                ItemTextContentNumb{
                    id : totalTxt
                    anchors{
                        top: discountTxt.bottom
                        topMargin: 42
                    }
                    height: 32
                    width: parent.width
                    title : "Total"
                    numb : orderModel.total
                }

                Rectangle{
                    height: 1
                    width: parent.width / 3
                    radius: 10
                    anchors.right: parent.right
                    anchors.rightMargin: 16
                    color: ms.color.stroke
                    anchors.margins: 8
                    anchors.top: discountTxt.bottom
                    anchors.topMargin: 28
                }

                Item {
                    id : modeContainer
                    width: parent.width
                    height: childrenRect.height
                    anchors{
                        top: totalTxt.bottom
                        bottom: btnCheckout.top
                        left: parent.left
                        right: parent.right
                        margins: 16
                    }

                    LargeIconButton{
                        id : btnCash
                        anchors.left: parent.left
                        width: parent.width/2 - 8
                        btn_name: "Cash"
                        ic_src: "qrc:/icons/ic_database.png"
                        isActive: true
                        onBtnClicked: {
                            if(!isActive){
                                isActive = !isActive
                                btnBanking.isActive = !btnBanking.isActive
                            }
                        }
                    }

                    LargeIconButton{
                        id : btnBanking
                        width: parent.width/2 - 8
                        anchors.right: parent.right
                        btn_name: "Banking"
                        ic_src: "qrc:/icons/ic_scan.png"
                        onBtnClicked: {
                            if(!isActive){
                                isActive = !isActive
                                btnCash.isActive = !btnCash.isActive
                            }
                        }
                    }
                }


                ButtonOutline{
                    name: "Checkout"
                    id : btnCheckout
                    height: ms.LoginScreen.action_button.height
                    width: ms.LoginScreen.action_button.width
                    anchors{
                        bottom: parent.bottom
                        bottomMargin: 32
                        horizontalCenter: parent.horizontalCenter
                    }
                    onBtnClicked: {
                        checkoutConfirmPopup.isCash = btnCash.isActive
                        checkoutConfirmPopup.open()
                    }
                    enabled: orderModel.orderDataView.rowCount > 0
                }

                Connections{
                    target: orderModel.orderDataView
                    onModelReset: btnCheckout.enabled =  orderModel.orderDataView.rowCount > 0
                    onOrderDataChanged:btnCheckout.enabled =  orderModel.orderDataView.rowCount > 0
                }
            }
        }
    }
}
