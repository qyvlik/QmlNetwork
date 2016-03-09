#ifndef QMLNETWORKDISKCACHE_H
#define QMLNETWORKDISKCACHE_H

#include <QNetworkDiskCache>

class QmlNetworkDiskCache : public QNetworkDiskCache
{
    Q_OBJECT
public:
    explicit QmlNetworkDiskCache(QObject *parent = 0);
};

#endif // QMLNETWORKDISKCACHE_H
