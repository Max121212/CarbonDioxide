#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLineSeries>
#include <QChartView>

#include "AverageCalculator.h"
#include "CarbonDioxideSensor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    /* Instantiate sensor símulation and average calculator. Start sensor simulation. */
    CarbonDioxideSensor sensor(nullptr, 0, 100, 3, 5);
    AverageCalculator avgCalculator;
    sensor.start();

    QQmlApplicationEngine engine;

    /* Set context properties to access sensor and average calculator data from QML including CalculationType enum. */
    engine.rootContext()->setContextProperty("sensor", &sensor);
    engine.rootContext()->setContextProperty("averageCalculator", &avgCalculator);
    qmlRegisterUncreatableType<AverageCalculator>("AverageCalculator.CalculationType", 1, 0, "AverageCalculator", "Enum cannot be instantiated");

    QObject::connect(&sensor, &CarbonDioxideSensor::publishSensorValue,
                     &avgCalculator, &AverageCalculator::receiveSensorValue);

    const QUrl url(u"qrc:/main.qml"_qs);
    engine.load(url);

    return app.exec();
}
