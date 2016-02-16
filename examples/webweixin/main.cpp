#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>

#include <qmlnetwork/qmlnetworkaccessmanager.h>
#include <qmlnetwork/qmlnetworkrequest.h>
#include <qmlnetwork/qmlnetworkresponse.h>

#include <qmlio/qmliodevice.h>
#include <qmlio/qmlbuffer.h>
#include <qmlio/qmlfileio.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<
            QmlNetworkAccessManager
            >("Network",
              1,
              0,
              "NetworkAccessManager");

    qmlRegisterType<
            QmlNetworkRequest
            >("Network",
              1,
              0,
              "NetworkRequest");

    qmlRegisterType<
            QmlNetworkResponse
            >("Network",
              1,
              0,
              "NetworkResponse");

    qmlRegisterUncreatableType<
            QmlIODevice
            >("Network",
              1,
              0,
              "IODevice",
              "IODevice is Abstract class");

    qmlRegisterUncreatableType<
            QmlNetworkAbstractResponse
            >("Network",
              1,
              0,
              "NetworkAbstractResponse",
              "NetworkAbstractResponse is Abstract class");


    qmlRegisterType<QmlBuffer>("Network",
                               1,
                               0,
                               "Buffer");

    qmlRegisterType<QmlFileIO>("Network",
                               1,
                               0,
                               "FileIO");


    QQmlApplicationEngine engine;


    engine.addImportPath("qrc:/qml/");
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    return app.exec();
}





