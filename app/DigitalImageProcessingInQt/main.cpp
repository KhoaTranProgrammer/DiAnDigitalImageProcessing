#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>
#include "DIPShowImage.h"
#include "DIPFeatures.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view;

    // Register DIPShowImage as QML type
    qmlRegisterType<DIPShowImage>("DIPShowImage", 1, 0, "DIPShowImage");

    // Create the instance of DIPFeatures, this object is used by QML application
    // to access C library
    view.engine()->rootContext()->setContextProperty("dipFeatures", DIPFeatures::getInstance());

    // Set input image default location
    view.engine()->rootContext()->setContextProperty("defaultinput", PROJECT_PATH);

    QObject::connect((QObject*)view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    view.setSource(QUrl("qrc:/main.qml"));
    view.showFullScreen();
    return app.exec();
}
