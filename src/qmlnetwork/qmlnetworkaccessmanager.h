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
    Q_PROPERTY(QString cacheDirectory READ cacheDirectory WRITE setCacheDirectory NOTIFY cacheDirectoryChanged)
    Q_PROPERTY(qint64 maximumCacheSize READ maximumCacheSize WRITE setMaximumCacheSize NOTIFY maximumCacheSizeChanged)

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

    QString cacheDirectory() const;

    void setCacheDirectory(const QString cachePath);

    qint64 maximumCacheSize()const;

    void setMaximumCacheSize(const qint64 cacheSize);

Q_SIGNALS:
    void cacheDirectoryChanged();
    void maximumCacheSizeChanged();

public Q_SLOTS:

private:
    QNetworkAccessManager* d_ptr;
};

#endif // QMLNETWORKACCESSMANAGER_H
