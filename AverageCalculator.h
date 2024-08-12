#ifndef AVERAGECALCULATOR_H
#define AVERAGECALCULATOR_H

#include <QObject>
#include <QDebug>
#include <QTimer>

class AverageCalculator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int averageValue MEMBER averageValue_ NOTIFY averageUpdated)

public:
    explicit AverageCalculator(QObject *parent = nullptr);
    ~AverageCalculator() = default;

signals:
    void averageUpdated();

public slots:
    void calculateAverage(int sensorValue);
    void setCalculationType(int type);

private:
    int averageValue_;
    int sum_;
    int count_;
};

#endif // AVERAGECALCULATOR_H
