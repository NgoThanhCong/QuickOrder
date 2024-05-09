import QtQuick 2.0
import "../common"

CardBase {
    id : rootCard
    height: childrenRect.height

    ItemTextContentNumb{
        title: "Dashboard"
        height: 32
        id : dashboardTxt
        anchors{
            top: parent.top
            left: parent.left
            margins : 8
        }
    }

    // TextTitle{
    //     id : overviewTxt
    //     height: 32
    //     anchors{
    //         top: dashboardTxt.bottom
    //         left: parent.left
    //         right: parent.right
    //         margins : 8
    //     }
    //     font.pixelSize: 28
    //     font.bold: true
    //     text : "Overview"
    // }

    Row{
        id : timeContainer
        anchors{
            top: dashboardTxt.bottom
            left: parent.left
            right: parent.right
            margins : 16
        }
        height: 50
        spacing: 8
        ButtonDefault{
            name : "12 Months"
            width: 80
            id: btnMonth
            color: ms.color.gray
            onBtnClicked: {
                btnMonth.color = ms.color.primary
                btn30Days.color = ms.color.gray
                btn7Days.color = ms.color.gray
            }
        }
        ButtonDefault{
            name : "30 Days"
            width: 80
            id : btn30Days
            color: ms.color.gray
            onBtnClicked: {
                btnMonth.color = ms.color.gray
                btn30Days.color = ms.color.primary
                btn7Days.color = ms.color.gray
            }
        }
        ButtonDefault{
            name : "7 Days"
            width: 80
            id : btn7Days
            onBtnClicked: {
                btnMonth.color = ms.color.gray
                btn30Days.color = ms.color.gray
                btn7Days.color = ms.color.primary
            }
        }
    }

    ImageButton{
        antialiasing: true
        src: "qrc:/icons/ic_export.png"
        height: 64
        width: 64
        icHeight: 64
        icWidth: 64
        anchors{
            verticalCenter: parent.verticalCenter
            right: parent.right
            margins: 8
        }
        onBtnClicked: ReportScreenController.exportData(7);
    }

}
