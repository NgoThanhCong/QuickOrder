import QtQuick 2.0
import "../common"
import QtCharts 2.13
import QtQml 2.0

CardBase {

    property var model : reportModel.categoryStatistic

    Connections{
        target: reportModel
        onCategoryStatisticChanged : {
            chart.updatePieChart();
        }
    }

    ChartView {
        id: chart
//        title: "Income by Category"
        backgroundColor: "transparent"
        anchors{
            top:parent.top
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins : -16
        }

        legend.alignment: Qt.AlignLeft
        antialiasing: true

        PieSeries {
            id: pieSeries
        }

        function updatePieChart(){
            for(var i =0 ;i < 6 ;i++){
                console.log("Pie Element:" + model[i].name + " - " + model[i].totalAmount)
                pieSeries.append(model[i].name, model[i].totalAmount)
                if(i == 0) {
                    pieSeries.at(0).labelVisible = true
                    pieSeries.at(0).exploded = true;
                }

            }
        }
    }

    Component.onCompleted: {
        chart.updatePieChart();
    }

}
