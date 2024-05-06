import QtQuick 2.12
import "../common"
import "../component"

Rectangle{
    color: "#F9F9F9"

    property var reportController: ReportScreenController
    property var reportModel: ReportScreenModel

    CardHeader{
        id : cardHeader
        width: parent.width / 2
        anchors{
            left: parent.left
            top: parent.top
            margins : 8
        }
    }

    CardBestSeller{
        id : cardBestSeller
        width: parent.width / 2
        anchors{
            top: parent.top
            right: parent.right
            left: cardHeader.right
            margins: 8
        }
    }

    Row {
        id : rowCardInfos
        width: parent.width
        height: 80
        anchors {
             left: parent.left
             right: cardBestSeller.left
             rightMargin: 35
             margins: 8
             top: cardHeader.bottom
        }

        spacing: 8

        CardInfo {
            height: parent.height
            title: reportModel.totalOrder.name
            contentTxt: reportModel.totalOrder.info
            width: parent.width / 4
        }

        CardInfo {
            height: parent.height
            title: reportModel.totalIncome.name
            contentTxt: reportModel.totalIncome.info
            width: parent.width / 4
        }

        CardInfo {
            height: parent.height
            title: reportModel.totalIncomeCash.name
            contentTxt: reportModel.totalIncomeCash.info
            width: parent.width / 4
        }

        CardInfo {
            height: parent.height
            title: reportModel.totalIncomeBanking.name
            contentTxt: reportModel.totalIncomeBanking.info
            width: parent.width / 4
        }
    }

    CardStatistic{
        id : cardStatistic
        anchors {
            top: cardBestSeller.bottom
            bottom: parent.bottom
            margins: 8
            right: parent.right
            left: cardHeader.right
        }
        width: parent.width
    }

    Item{
        anchors {
            top: rowCardInfos.bottom
            bottom: parent.bottom
            left: parent.left
            right: cardStatistic.left
            margins: 8
        }

        CardCategoryStatistic{
            id : cateStatistic
            height: parent.height * (2/5)
            width: parent.width
        }

        CardHottestTime{
            anchors.top: cateStatistic.bottom
            anchors.topMargin: 8
            height: parent.height * (3/5)
            width: parent.width
            anchors.bottom: parent.bottom
        }

    }
}
