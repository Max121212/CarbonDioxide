#include "AverageCalculator.h"

#include <QDebug>

AverageCalculator::AverageCalculator(QObject *parent)
    : QObject(parent), sum_(0), count_(0), averageValue_(0)
{
    
}

void AverageCalculator::calculateAverage(int sensorValue)
{
    sum_ += sensorValue;
    count_++;
    averageValue_ = sum_ / count_;
    emit averageUpdated(); // Notify that the average has been updated
}

void AverageCalculator::setCalculationType(int type)
{
    qDebug() << "Type chosen: " << type;
}