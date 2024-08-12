#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CarbonDioxideSensor.h"
#include "AverageCalculator.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    CarbonDioxideSensor sensor;
    AverageCalculator avgCalculator;
    sensor.start();

    QObject::connect(&sensor, &CarbonDioxideSensor::publishSensorUpdate,
                     &avgCalculator, &AverageCalculator::calculateAverage);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("sensor", &sensor);
    engine.rootContext()->setContextProperty("averageCalculator", &avgCalculator);
    const QUrl url(u"qrc:/main.qml"_qs);


    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
