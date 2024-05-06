import QtQuick 2.0
import "../common"
import QtCharts 2.13
import QtQml 2.3

CardBase {
    property var model: reportModel.dateStatistic

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

    ChartView {
        title: "Revenue Statistics"
        titleColor: ms.color.primary
        titleFont.bold: true
        anchors.fill: parent
        antialiasing: true
        legend.visible: false

        LineSeries {
            id : lineSeries
            axisX: DateTimeAxis {
                format: "dd MMM"
                tickCount: 7
            }

             axisY: ValueAxis {
                 min: 0
                 max: 5000
             }

            //Fuction to convert dd.mm.YYYY to msecs
            function toMsecsSinceEpoch(dateString) {
                var [day, month, year] = dateString.split(".");
                console.log(parseInt(day))
                var date = new Date(2024, 3, parseInt(day));
                var msecs = date.getTime();
                console.log(msecs);
                return msecs;
            }

            // // Please note that month in JavaScript months are zero based, so 2 means March
            XYPoint { x: lineSeries.toMsecsSinceEpoch("24.04.2024"); y: 4705 }
            XYPoint { x: lineSeries.toMsecsSinceEpoch("25.04.2024"); y: 1999 }
            XYPoint { x: lineSeries.toMsecsSinceEpoch("26.04.2024"); y: 1594 }
            XYPoint { x: lineSeries.toMsecsSinceEpoch("27.04.2024"); y: 2170 }
            XYPoint { x: lineSeries.toMsecsSinceEpoch("28.04.2024"); y: 2867 }
            XYPoint { x: lineSeries.toMsecsSinceEpoch("29.04.2024"); y: 1951 }
            XYPoint { x: lineSeries.toMsecsSinceEpoch("30.04.2024"); y: 1353 }

            function updateChart(){
                console.log("updateChart")
                for(var i =0 ;i < reportModel.getDateStatisticSize() ;i++){
                    console.log("LineSeries:" + model[i].date + " - " + model[i].value)
                    lineSeries.append(lineSeries.toMsecsSinceEpoch(model[i].date),parseInt(i))
                }
            }
        }
    }

    Component.onCompleted: {
        // lineSeries.updateChart();
    }

}
