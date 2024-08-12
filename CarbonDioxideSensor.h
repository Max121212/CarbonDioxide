#ifndef CARBONDIOXIDESENSOR_H
#define CARBONDIOXIDESENSOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QMutex>
#include <QWaitCondition>

class CarbonDioxideSensor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int carbonDioxideValue MEMBER carbonDioxideValue_ NOTIFY publishSensorUpdate)
    Q_PROPERTY(int targetValue MEMBER targetValue_ NOTIFY publishTargetValue)

public:
    explicit CarbonDioxideSensor(QObject *parent = nullptr);
    ~CarbonDioxideSensor() override;

    void start();

signals:
    void publishSensorUpdate(int sensorValue);
    void publishTargetValue();

public slots:
    void updateSensorValue();

private:
    QTimer* updateTimer_; // Timer to handle periodic updates
    int carbonDioxideValue_;
    int targetValue_; // Store the current target value
    bool targetValueSet_; // Flag to check if target value is set
};

#endif // CARBONDIOXIDESENSOR_H
