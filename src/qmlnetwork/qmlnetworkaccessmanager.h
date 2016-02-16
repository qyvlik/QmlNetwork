#ifndef QMLNETWORKACCESSMANAGER_H
#define QMLNETWORKACCESSMANAGER_H

#include <QObject>
#include <QJSValue>

class QmlNetworkRequest;
class QmlNetworkResponse;
class QNetworkAccessManager;

class QmlNetworkAccessManager : public QObject
{
    Q_OBJECT
public:
    explicit QmlNetworkAccessManager(QObject *parent = 0);
    ~QmlNetworkAccessManager();

    //! asynchronous
    Q_INVOKABLE bool post(QmlNetworkRequest* request, QmlNetworkResponse* response);

    //! asynchronous
    Q_INVOKABLE bool get(QmlNetworkRequest* request, QmlNetworkResponse* response);

    //! asynchronous
    Q_INVOKABLE bool head(QmlNetworkRequest* request, QmlNetworkResponse* response);

    //! asynchronous
    Q_INVOKABLE bool put(QmlNetworkRequest* request, QmlNetworkResponse* response);

    //! asynchronous
    Q_INVOKABLE bool deleteResource(QmlNetworkRequest* request, QmlNetworkResponse* response);

Q_SIGNALS:

public Q_SLOTS:

private:
    QNetworkAccessManager* d_ptr;
};

#endif // QMLNETWORKACCESSMANAGER_H
