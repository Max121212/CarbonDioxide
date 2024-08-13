import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtCharts 2.15
import AverageCalculator.CalculationType 1.0

ApplicationWindow {
    visible: true
    width: 1600
    height: 900
    title: qsTr("Carbon dioxide sensor simulation and average calculation")

    ColumnLayout {
        id: clmlyt_simulationAndCalculation
        spacing: 10

        // Header for the CO2 sensor simulation section
        Label {
            id: lbl_headerSimulation
            text: qsTr("Carbon dioxide sensor simulation: ")
            font.pointSize: 24
            font.bold: true
        }
    
        // Label displaying the current CO2 level
        Label {
            id: lbl_carbonDioxideValue
            text: qsTr("CO2-Level: " + sensor.carbonDioxideValue)
            font.pointSize: 20
            font.bold: false
        }

        // Label displaying the current target CO2 level
        Label {
            id: lbl_carbonDioxideTarget
            text: qsTr("Current target CO2-Level: " + sensor.targetValue)
            font.pointSize: 20
            font.bold: false
        }
    
        // Header for the average calculation section
        Label {
            id: lbl_headerCalculation
            text: qsTr("Average calculation: ")
            font.pointSize: 24
            font.bold: true
            Layout.topMargin: 20
        }

        // Label for the calculation type selection
        Label {
            id: lbl_calculationTypeHeading
            text: "Choose calculation type: "
            font.pointSize: 20
            font.bold: false
        }

        // ComboBox for selecting the calculation type (Average or Median)
        ComboBox {
            id: cbx_calculationType
            model: ["Average", "Median"]

            // Update the calculation type in the backend when selection changes
            onActivated: function(index) {
                if (index === 0) {
                    averageCalculator.setCalculationType(AverageCalculator.AVERAGE);
                } else if (index === 1) {
                    averageCalculator.setCalculationType(AverageCalculator.MEDIAN);
                }
            }
        }

        // Label for the record time slider
        Label {
            id: lbl_recordTimeSliderHeading
            text: "Record time: "
            font.pointSize: 20
            font.bold: false
        }

        RowLayout {
            // Slider for selecting the number of seconds to record sensor data
            Slider {
                id: sld_recordTime
                from: 10
                value: 20
                to: 30
                stepSize: 5
                snapMode: Slider.SnapAlways

                // Update the label and backend when the slider is moved
                onMoved: function() {
                    lbl_recordTime.text = value + "s"
                    averageCalculator.setCapturedSensorValuesAmount(value)
                }
            }

            // Label displaying the current value of the record time slider
            Label {
                id: lbl_recordTime
                text: "20s"
                font.pointSize: 20
                font.bold: false
            }
        }

        // Label displaying the current average CO2 level
        Label {
            id: lbl_carbonDioxideAverage
            text: qsTr("Current average CO2-Level: " + averageCalculator.averageValue)
            font.pointSize: 20
            font.bold: false
        }
    }

    Item {
        width: parent.width
        height: 500
        anchors.top: clmlyt_simulationAndCalculation.bottom

        // ChartView to visualize the CO2 data
        ChartView {
            id: chartView
            anchors.fill: parent
            title: "Data Plot"
            legend.visible: true

            // LineSeries for displaying the sensor data over time
            LineSeries {
                id: lineSeries
                name: "Data"
                axisX: xAxis
                axisY: yAxis
            }

            // ScatterSeries for displaying the current average value
            ScatterSeries {
                id: scatterSeriesAverage
                name: "DataAverage"
                axisX: xAxis
                axisY: yAxis
            }

            // X-axis for the chart, representing time
            ValueAxis {
                id: xAxis
                titleText: "Time"
                min: 0
                max: 30
            }

            // Y-axis for the chart, representing CO2 levels
            ValueAxis {
                id: yAxis
                titleText: "CO2 Level"
                min: 0
                max: 100
            }
        }
    }
    
    // Connection to handle updates to the line series when the sensor values change
    Connections {
        target: averageCalculator
        function onValuesLineSeriesChanged(){
            lineSeries.clear();  // Clear existing data
            var data = averageCalculator.valuesLineSeries;
            for (var i = 0; i < data.length; i++) {
                lineSeries.append(i, data[i]);  // Append new data points
            }
        }
    }

    // Connection to handle updates to the scatter series when the average value changes
    Connections {
        target: averageCalculator
        function onAverageUpdated(){
            scatterSeriesAverage.clear();  // Clear existing data
            scatterSeriesAverage.append(0, averageCalculator.averageValue);  // Add the new average value
        }
    }
}
