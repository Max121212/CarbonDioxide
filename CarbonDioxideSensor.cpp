#include "CarbonDioxideSensor.h"
#include <QRandomGenerator>
#include <cmath> // For std::abs

CarbonDioxideSensor::CarbonDioxideSensor(QObject *parent)
    : QObject(parent), carbonDioxideValue_(0), targetValue_(0), targetValueSet_(false)
{
    updateTimer_ = new QTimer(this);
    connect(updateTimer_, &QTimer::timeout, this, &CarbonDioxideSensor::updateSensorValue);
}

CarbonDioxideSensor::~CarbonDioxideSensor()
{
    if (updateTimer_->isActive()) {
        updateTimer_->stop();
    }
}

void CarbonDioxideSensor::start()
{
    updateTimer_->start(1000); // Update every second
}

void CarbonDioxideSensor::updateSensorValue()
{
    const int minValue = 0;
    const int maxValue = 100;
    const int smoothingFactor = 1; // Smoothing step size
    const int tolerance = 1; // Tolerance to consider the target value reached

    if (!targetValueSet_) {
        targetValue_ = QRandomGenerator::global()->bounded(minValue, maxValue + 1);
        targetValueSet_ = true;
        emit publishTargetValue();
    }

    // Smooth transition towards the target value
    if (carbonDioxideValue_ < targetValue_) {
        carbonDioxideValue_ = qMin(carbonDioxideValue_ + smoothingFactor, targetValue_);
    } else if (carbonDioxideValue_ > targetValue_) {
        carbonDioxideValue_ = qMax(carbonDioxideValue_ - smoothingFactor, targetValue_);
    }

    // Emit the signal
    emit publishSensorUpdate(carbonDioxideValue_);

    // Check if the current value is close enough to the target
    if (std::abs(carbonDioxideValue_ - targetValue_) <= tolerance) {
        targetValueSet_ = false; // Set flag to generate a new target value in the next iteration
    }
}
