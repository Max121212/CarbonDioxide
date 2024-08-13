#include "CarbonDioxideSensor.h"
#include <QRandomGenerator>
#include <cmath>

CarbonDioxideSensor::CarbonDioxideSensor(QObject *parent, int minValue, int maxValue, int smoothingFactor, int tolerance)
    : QObject(parent), carbonDioxideValue_(0), targetValue_(0), targetValueSet_(false), minValue_(minValue), maxValue_(maxValue), 
    smoothingFactor_(smoothingFactor), tolerance_(tolerance)
{
    // Initialize the timer and connect it to the updateSensorValue slot
    updateTimer_ = new QTimer(this);
    connect(updateTimer_, &QTimer::timeout, this, &CarbonDioxideSensor::updateSensorValue);
}

CarbonDioxideSensor::~CarbonDioxideSensor()
{
    // Stop the timer if it's active before destruction
    if (updateTimer_->isActive()) {
        updateTimer_->stop();
    }
}

void CarbonDioxideSensor::start()
{
    // Start the timer with a 1000 ms (1 second) interval
    updateTimer_->start(1000);
}

void CarbonDioxideSensor::updateSensorValue()
{
    // If the target value has not been set, generate a new random target value
    if (!targetValueSet_) {
        targetValue_ = QRandomGenerator::global()->bounded(minValue_, maxValue_ + 1);
        targetValueSet_ = true;
        emit publishTargetValue(); // Emit signal to notify that the target value has changed
    }

    // Smoothly transition the current value towards the target value
    if (carbonDioxideValue_ < targetValue_) {
        carbonDioxideValue_ = qMin(carbonDioxideValue_ + smoothingFactor_, targetValue_);
    } else if (carbonDioxideValue_ > targetValue_) {
        carbonDioxideValue_ = qMax(carbonDioxideValue_ - smoothingFactor_, targetValue_);
    }

    // Emit the signal to notify that the sensor value has been updated
    emit publishSensorValue(carbonDioxideValue_);

    // If the current value is within the tolerance range of the target, prepare for a new target
    if (std::abs(carbonDioxideValue_ - targetValue_) <= tolerance_) {
        targetValueSet_ = false; // Reset flag to generate a new target value in the next update
    }
}
