#include "AverageCalculator.h"
#include <QDebug>
#include <QVector>
#include <QtCharts/QLineSeries>

AverageCalculator::AverageCalculator(QObject *parent)
    : QObject(parent), averageValue_(0), calculationType_(CalculationType::AVERAGE),
      capturedSensorValuesAmount_(20)
{
    // Constructor: Initializes the average value, sets the default calculation type, and sets the default number of captured sensor values.
}

void AverageCalculator::receiveSensorValue(int sensorValue)
{
    // If the number of sensor values exceeds 30, remove the oldest value.
    if (sensorValues_.size() >= 30) {
        sensorValues_.pop_front();  // Remove the oldest value
    }
    sensorValues_.append(sensorValue);  // Add the new sensor value to the list

    // Recalculate the average based on the current calculation type and sensor values.
    averageValue_ = calculate(calculationType_, sensorValues_);

    // Emit signals to notify that the average value and line series have been updated.
    emit averageUpdated();
    emit valuesLineSeriesChanged();
}

void AverageCalculator::setCalculationType(CalculationType type)
{
    // Sets the type of calculation (Average or Median) to be used.
    calculationType_ = type;
}

void AverageCalculator::setCapturedSensorValuesAmount(int amount)
{
    // Sets the number of sensor values to consider when calculating the average or median.
    capturedSensorValuesAmount_ = amount;
}

double AverageCalculator::calculate(CalculationType type, QVector<int> sensorValues)
{
    // If there are no sensor values, return 0.
    if (sensorValues.isEmpty()) {
        return 0.0;
    }

    QVector<int> tmpValues;

    // If the number of sensor values exceeds the captured amount, only consider the latest values.
    if (sensorValues.size() > capturedSensorValuesAmount_) {
        tmpValues = sensorValues.mid(sensorValues.size() - capturedSensorValuesAmount_, sensorValues.size());
    } else {
        tmpValues = sensorValues;
    }

    // Calculate either the average or the median based on the selected calculation type.
    switch (calculationType_) {
        case CalculationType::AVERAGE:
        {
            int sum = 0;
            for (int value : tmpValues) {
                sum += value;
            }
            return static_cast<double>(sum) / tmpValues.size();
        }
        case CalculationType::MEDIAN:
        {
            // Sort the values to calculate the median.
            std::sort(tmpValues.begin(), tmpValues.end());
            int size = tmpValues.size();
            if (size % 2 == 1) {
                return static_cast<double>(tmpValues[size / 2]);
            } else {
                int midIndex = size / 2;
                return (tmpValues[midIndex - 1] + tmpValues[midIndex]) / 2.0;
            }
        }
        default:
        {
            return 0.0;
        }
    }
}

QVariantList AverageCalculator::valuesLineSeries() const
{
    QVariantList list;

    // If the number of sensor values exceeds the captured amount, only consider the latest values.
    if (sensorValues_.size() > capturedSensorValuesAmount_) {
        QVector<int> tmpValues;
        tmpValues = sensorValues_.mid(sensorValues_.size() - capturedSensorValuesAmount_, sensorValues_.size());
        for (double value : tmpValues) 
        {
            list.append(value);  // Add each value to the QVariantList for use in the line series.
        }
    } else {
        for (double value : sensorValues_) 
        {
            list.append(value);  // Add each value to the QVariantList for use in the line series.
        }
    }
    return list;
}
