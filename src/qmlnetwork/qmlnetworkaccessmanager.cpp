#include "qmlnetworkaccessmanager.h"

#include "qmlnetworkrequest.h"
#include "qmlnetworkresponse.h"
#include "../qmlio/qmliodevice.h"

#include <QNetworkAccessManager>
#include <QBuffer>
#include <QDebug>

QmlNetworkAccessManager::QmlNetworkAccessManager(QObject *parent)
    : QObject(parent),
      d_ptr(new QNetworkAccessManager(this))
{
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

