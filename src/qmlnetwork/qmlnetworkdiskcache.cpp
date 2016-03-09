#include "qmlnetworkdiskcache.h"

#include <QStandardPaths>
#include <qdebug.h>

QmlNetworkDiskCache::QmlNetworkDiskCache(QObject *parent)
    : QNetworkDiskCache(parent)
{
    QString cachePath = QStandardPaths::displayName(QStandardPaths::CacheLocation);

#ifdef QT_DEBUG
    qDebug() << "cache path:" << cachePath;
#endif

    setCacheDirectory(cachePath);
    setMaximumCacheSize(100 * 1024 * 1024);
}

