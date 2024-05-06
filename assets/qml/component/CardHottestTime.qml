import QtQuick 2.0
import "../common"
import QtCharts 2.13

CardBase {

    ChartView {
        title: "Good time for sell !"
        titleFont.bold: true
        titleColor: ms.color.primary
        backgroundColor: "transparent"


        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins : -16
        }

        legend.visible: false
        antialiasing: true

        BarSeries {
            axisX: BarCategoryAxis { categories: ["08h", "09h", "10h", "11h", "12h", "13h", "14h",
                    "15h", "16h", "17h", "18h", "19h", "20h", "21h", "22h"]
                labelsFont.pixelSize: 10

            }
            axisY: ValueAxis{
                min: 0
                max: 35
                titleFont.pixelSize: 10
            }

            BarSet { label: "Order"; values: [0 ,1 ,15,30,0 ,3 ,17,14,12,14,1 ,2 ,17,19,3] }
        }
    }

}
