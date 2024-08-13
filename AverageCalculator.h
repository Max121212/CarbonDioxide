#ifndef AVERAGECALCULATOR_H
#define AVERAGECALCULATOR_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QList>
#include <QtCharts/QLineSeries>

/**
 * @class AverageCalculator
 * @brief The AverageCalculator class provides a mechanism for calculating and maintaining
 * an average or median of sensor values.
 * 
 * The class receives sensor values, stores them, and calculates either an average or median
 * depending on the selected calculation type. The class emits signals when the calculated 
 * value or the underlying data changes, allowing it to be connected to UI elements or other 
 * components.
 */
class AverageCalculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList valuesLineSeries READ valuesLineSeries NOTIFY valuesLineSeriesChanged) ///< Exposes the list of sensor values for the chart in QML
    Q_PROPERTY(double averageValue READ averageValue NOTIFY averageUpdated) ///< Exposes the current average value of the sensor data in QML

public:
    /**
     * @brief Constructs an AverageCalculator object.
     * 
     * @param parent Pointer to the parent QObject, default is nullptr.
     */
    explicit AverageCalculator(QObject *parent = nullptr);

    /**
     * @brief Destructor for AverageCalculator.
     */
    ~AverageCalculator() = default;

    /**
     * @brief Retrieves the current list of sensor values for use in a line series chart.
     * 
     * @return QVariantList containing the sensor values.
     */
    QVariantList valuesLineSeries() const;

    /**
     * @enum CalculationType
     * @brief Enumeration for selecting the type of calculation.
     */
    enum class CalculationType
    {
        AVERAGE = 1, ///< Calculates the average of the sensor values.
        MEDIAN = 2   ///< Calculates the median of the sensor values.
    };
    Q_ENUMS(CalculationType)

signals:
    /**
     * @brief Signal emitted when the average value is updated.
     */
    void averageUpdated();

    /**
     * @brief Signal emitted when the line series (sensor values) are updated.
     */
    void valuesLineSeriesChanged();

public slots:
    /**
     * @brief Slot to receive a new sensor value.
     * 
     * Adds the new sensor value to the list, updates the calculation, and emits relevant signals.
     * 
     * @param sensorValue The new sensor value to be added.
     */
    void receiveSensorValue(int sensorValue);

    /**
     * @brief Sets the type of calculation to be performed (average or median).
     * 
     * @param type The calculation type to set.
     */
    void setCalculationType(CalculationType type);

    /**
     * @brief Sets the number of sensor values to consider in the calculation.
     * 
     * @param amount The number of recent sensor values to capture.
     */
    void setCapturedSensorValuesAmount(int amount);

    /**
     * @brief Returns the current average value.
     * 
     * @return The current average value as a double.
     */
    double averageValue() const { return averageValue_; }

private:
    /**
     * @brief Calculates the result based on the specified calculation type and sensor values.
     * 
     * @param type The calculation type (average or median).
     * @param sensorValues The list of sensor values to consider in the calculation.
     * 
     * @return The calculated result as a double.
     */
    double calculate(CalculationType type, QVector<int> sensorValues);

    double averageValue_; ///< The current calculated average or median value.
    CalculationType calculationType_; ///< The type of calculation to perform.
    int capturedSensorValuesAmount_; ///< The number of sensor values to consider in the calculation.
    QVector<int> sensorValues_; ///< The list of recent sensor values.
};

#endif // AVERAGECALCULATOR_H
