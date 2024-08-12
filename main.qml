import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello, Qt6 with QML!")

    Label {
        id: lbl_carbonDioxideValue
        text: qsTr("CO2-Level: " + sensor.carbonDioxideValue)
    }

    Label {
        id: lbl_carbonDioxideTarget
        text: qsTr("Current target CO2-Level: " + sensor.targetValue)

        anchors {
            top: lbl_carbonDioxideValue.bottom
            topMargin: 10
        }
    }

    Label {
        id: lbl_carbonDioxideAverage
        text: qsTr("Current average CO2-Level: " + averageCalculator.averageValue)

        anchors {
            top: lbl_carbonDioxideTarget.bottom
            topMargin: 10
        }
    }

    ComboBox {
        model: ["Average", "Median"]
        onActivated: 
        {
            averageCalculator.setCalculationType(index)
        }

        anchors
        {
            centerIn: parent
        }
    }
}