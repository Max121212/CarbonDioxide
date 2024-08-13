#ifndef CARBONDIOXIDESENSOR_H
#define CARBONDIOXIDESENSOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>

/**
 * @brief The CarbonDioxideSensor class simulates a carbon dioxide sensor.
 *
 * This class simulates a carbon dioxide sensor which randomly sets a target value 
 * between a specified range (minValue to maxValue) and adjusts the current sensor 
 * value towards this target over time, using a smoothing factor and tolerance to 
 * determine the rate of change.
 */
class CarbonDioxideSensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int carbonDioxideValue MEMBER carbonDioxideValue_ NOTIFY publishSensorValue) ///< Q_PROPERTY used for publishing the current CO2 value to the UI
    Q_PROPERTY(int targetValue MEMBER targetValue_ NOTIFY publishTargetValue) ///< Q_PROPERTY used for publishing the current CO2 target value to the UI

public:
    /**
     * @brief Constructs a CarbonDioxideSensor object.
     * 
     * @param parent The parent object. Defaults to nullptr.
     * @param minValue The minimum value that the sensor can report. Defaults to 0.
     * @param maxValue The maximum value that the sensor can report. Defaults to 100.
     * @param smoothingFactor The factor by which the sensor value approaches the target value.
                       Higher values will result in faster changes. Defaults to 1.
     * @param tolerance The allowable deviation from the target value before the sensor 
     *                  stops adjusting. Defaults to 1.
     */
    explicit CarbonDioxideSensor(QObject *parent = nullptr, int minValue = 0, int maxValue = 100, int smoothingFactor = 1, int tolerance = 1);

    /**
     * @brief Destroys the CarbonDioxideSensor object.
     */
    ~CarbonDioxideSensor() override;

    /**
     * @brief Starts the sensor simulation.
     *
     * This function initializes the sensor by starting a timer that periodically updates 
     * the sensor value, simulating the behavior of a real carbon dioxide sensor.
     */
    void start();

signals:
    /**
     * @brief Signal emitted when the sensor value is updated.
     *
     * @param sensorValue The new sensor value after an update.
     */
    void publishSensorValue(int sensorValue);

    /**
     * @brief Signal emitted when the target value is updated.
     */
    void publishTargetValue();

public slots:
    /**
     * @brief Updates the sensor value towards the target value.
     *
     * This slot is called periodically by the timer to update the sensor value. The value 
     * is adjusted towards the target value according to the smoothing factor and tolerance.
     */
    void updateSensorValue();

private:
    QTimer* updateTimer_; ///< Timer to handle periodic updates
    int carbonDioxideValue_; ///< Stores the current CO2 value reported by the sensor
    int targetValue_; ///< Stores the current target CO2 value
    bool targetValueSet_; ///< Flag indicating if a target value has been set

    int minValue_; ///< Minimum possible value for the sensor reading
    int maxValue_; ///< Maximum possible value for the sensor reading
    int smoothingFactor_; ///< Factor by which the sensor value is smoothed towards the target
    int tolerance_; ///< Tolerance within which the sensor value is considered to have reached the target
};

#endif // CARBONDIOXIDESENSOR_H
