#include "qmlnetworkaccessmanager.h"

#include "qmlnetworkrequest.h"
#include "qmlnetworkresponse.h"
#include "../qmlio/qmliodevice.h"
#include "qmlnetworkdiskcache.h"

#include <QNetworkAccessManager>
#include <QBuffer>
#include <QDebug>

QmlNetworkAccessManager::QmlNetworkAccessManager(QObject *parent)
    : QObject(parent),
      d_ptr(new QNetworkAccessManager(this))
{
    d_ptr->setCache(new QmlNetworkDiskCache(d_ptr));
}

QmlNetworkAccessManager::~QmlNetworkAccessManager()
{
    d_ptr->deleteLater();
}

bool QmlNetworkAccessManager::post(QmlNetworkRequest *request, QmlNetworkResponse *response)
{
    if(request && response) {
        if(request->ioDevice() && request->ioDevice()->device()) {
            //#ifdef QT_DEBUG
            //            QBuffer* buffer = dynamic_cast<QBuffer*>(request->ioDevice()->device());
            //            if(buffer){
            //                qDebug() << buffer->data() << endl;
            //            } else {
            //                qDebug() << "buffer is NULL!" << endl;
            //            }
            //#endif
            //qDebug() << request->ioDevice()->device();

            response->setReply( d_ptr->post(request->request(),
                                            request->ioDevice()->device()));

            //            qDebug() << "response->reply()->isFinished(): "
            //                     << response->reply()->isFinished();

            //            qDebug() << "request->ioDevice()->device()->atEnd():"
            //                     << request->ioDevice()->device()->atEnd();

        } else {
#ifdef QT_DEBUG
            qDebug() << Q_FUNC_INFO
                     << ": request->ioDevice(): " << request->ioDevice();
#endif
            response->setReply(d_ptr->post(request->request(), QByteArray("")));
        }
        return true;
    } else {
        return false;
    }
}

bool QmlNetworkAccessManager::get(QmlNetworkRequest *request, QmlNetworkResponse *response)
{
    if(request && response) {
        response->setReply( d_ptr->get(request->request()));
        return true;
    } else {
        return false;
    }
}

bool QmlNetworkAccessManager::head(QmlNetworkRequest *request, QmlNetworkResponse *response)
{
    if(request && response) {
        response->setReply(d_ptr->head(request->request()));
        return true;
    } else {
        return false;
    }
}

bool QmlNetworkAccessManager::put(QmlNetworkRequest *request, QmlNetworkResponse *response)
{
    if(request && response) {
        if(request->ioDevice() && request->ioDevice()->device()) {
            response->setReply( d_ptr->put(request->request(),
                                            request->ioDevice()->device()));
        } else {
#ifdef QT_DEBUG
            qDebug() << Q_FUNC_INFO
                     << ": request->ioDevice(): " << request->ioDevice();
#endif
            response->setReply(d_ptr->put(request->request(), QByteArray("")));
        }
        return true;
    } else {
        return false;
    }
}

bool QmlNetworkAccessManager::deleteResource(QmlNetworkRequest *request, QmlNetworkResponse *response)
{
    if(request && response) {
        response->setReply(d_ptr->deleteResource(request->request()));
        return true;
    } else {
        return false;
    }
}

QString QmlNetworkAccessManager::cacheDirectory() const
{
   QmlNetworkDiskCache *cacheObject = qobject_cast<QmlNetworkDiskCache*>(d_ptr->cache());
   if(cacheObject) {
       return cacheObject->cacheDirectory();
   } else {
       return QString();
   }
}

void QmlNetworkAccessManager::setCacheDirectory(const QString cachePath)
{
    QmlNetworkDiskCache *cacheObject = qobject_cast<QmlNetworkDiskCache*>(d_ptr->cache());
    if(cacheObject && cacheObject->cacheDirectory() != cachePath) {
        cacheObject->setCacheDirectory(cachePath);
        Q_EMIT cacheDirectoryChanged();
    }
}

qint64 QmlNetworkAccessManager::maximumCacheSize() const
{
    QmlNetworkDiskCache *cacheObject = qobject_cast<QmlNetworkDiskCache*>(d_ptr->cache());
    if(cacheObject) {
        return cacheObject->maximumCacheSize();
    } else {
        return 0;
    }
}

void QmlNetworkAccessManager::setMaximumCacheSize(const qint64 cacheSize)
{
    QmlNetworkDiskCache *cacheObject = qobject_cast<QmlNetworkDiskCache*>(d_ptr->cache());
    if(cacheObject && cacheObject->maximumCacheSize() != cacheSize) {
        cacheObject->setMaximumCacheSize(cacheSize);
        Q_EMIT maximumCacheSizeChanged();
    }
}

