#include "qmlnetworkabstractresponse.h"

#include <QNetworkRequest>
#include <QJsonObject>

QmlNetworkAbstractResponse::QmlNetworkAbstractResponse(QObject *parent)
    : QObject(parent),
      m_reply(Q_NULLPTR)
{
    qRegisterMetaType<NetworkError>("QmlNetworkAbstractResponse::NetworkError");
}

QmlNetworkAbstractResponse::~QmlNetworkAbstractResponse()
{
    //    if(m_reply) {
    //        m_reply->deleteLater();
    //        m_reply = Q_NULLPTR;
    //    }
}

QNetworkReply *QmlNetworkAbstractResponse::reply() const
{
    return this->m_reply;
}

void QmlNetworkAbstractResponse::setReply(QNetworkReply *reply)
{
    if(m_reply != reply) {
        this->clearOldReplyConnect();
        m_reply = reply;
        if(m_reply != Q_NULLPTR) {
            this->connectReplyObject();
        }
        emit replyChanged();
    }
}

QVariant QmlNetworkAbstractResponse::header(QmlNetworkRequest::KnownHeaders header) const
{
    if(m_reply) {
        return m_reply->header((QNetworkRequest::KnownHeaders)header);
    } else {
        return QVariant();
    }
}

QVariant QmlNetworkAbstractResponse::getResponseHeader(const QByteArray & headerName) const
{
    if(m_reply) {
        if(m_reply->isFinished()) {
            return m_reply->rawHeader(headerName);
        } else {
            return QVariant();
        }
    } else {
        return QVariant();
    }
}

QJsonArray QmlNetworkAbstractResponse::getAllResponseHeaders() const
{
    QJsonArray array;
    if(m_reply) {
        if(m_reply->isFinished()) {
            QList<QNetworkReply::RawHeaderPair>
                    list = this->m_reply->rawHeaderPairs();
            Q_FOREACH(const QNetworkReply::RawHeaderPair& iter, list) {
                array.push_back(QJsonValue(QString(iter.first)
                                           + ":"
                                           + QString(iter.second)));
            }
            return array;
        } else {
            return array;
        }
    } else {
        return array;
    }
}

QJsonArray QmlNetworkAbstractResponse::getAllResponseHeaderPairs() const
{
    QJsonArray array;
    if(m_reply) {
        if(m_reply->isFinished()) {
            QList<QNetworkReply::RawHeaderPair>
                    list = this->m_reply->rawHeaderPairs();
            Q_FOREACH(const QNetworkReply::RawHeaderPair& iter, list) {
                QJsonObject i;
                i.insert("header", QString(iter.first));
                i.insert("value", QString(iter.second));
                array.push_back(QJsonValue(i));
            }
            return array;
        } else {
            return array;
        }
    } else {
        return array;
    }
}

bool QmlNetworkAbstractResponse::isRunning() const
{
    return m_reply ? m_reply->isRunning() : false;
}

bool QmlNetworkAbstractResponse::isFinished() const
{
    return m_reply ? m_reply->isFinished() : false;
}

void QmlNetworkAbstractResponse::abort()
{
    if(m_reply) {
        m_reply->abort();
    }
}

void QmlNetworkAbstractResponse::ignoreSslErrors()
{
    if(m_reply) {
        m_reply->ignoreSslErrors();
    }
}


//qint64 QmlNetworkAbstractResponse::contentLength() const
//{
//    return m_reply != Q_NULLPTR
//            ? m_reply->header(QNetworkRequest::ContentLengthHeader).toLongLong()
//            : -1;
//}


void QmlNetworkAbstractResponse::clearOldReplyConnect()
{
    if(m_reply != Q_NULLPTR) {
        //! TODO
        //! remove... later
        disconnect(m_reply, 0, this, 0);
        m_reply->deleteLater();
        m_reply = Q_NULLPTR;
    }
}

/*
 *  void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void encrypted();
    void error(QNetworkReply::NetworkError code);
    void finished();
    void metaDataChanged();
    void preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator * authenticator);
    void sslErrors(const QList<QSslError> & errors);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void aboutToClose();
    void bytesWritten(qint64 bytes);
    void readChannelFinished();
    void readyRead();
*/

void QmlNetworkAbstractResponse::connectReplyObject()
{
    connect( m_reply, SIGNAL(finished()), this, SIGNAL(finished()) );

    connect( m_reply, SIGNAL(downloadProgress(qint64,qint64)),
             this, SIGNAL(downloadProgress(qint64,qint64)) );

    connect( m_reply, SIGNAL(encrypted()), this, SIGNAL(encrypted()) );

    connect( m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
             this, SIGNAL(error(QNetworkReply::NetworkError)) );

    connect( m_reply, SIGNAL(metaDataChanged()), this, SIGNAL(metaDataChanged()) );

    connect( m_reply, SIGNAL(preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator*)),
             this, SIGNAL(preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator*)) );

    connect( m_reply, SIGNAL(uploadProgress(qint64,qint64)),
             this, SIGNAL(uploadProgress(qint64,qint64)) );

    connect( m_reply, SIGNAL(aboutToClose()),
             this, SIGNAL(aboutToClose()) );

    //    connect( m_reply, SIGNAL(bytesWritten(qint64 bytes)),
    //             this, SIGNAL(bytesWritten(qint64 bytes)));

    connect( m_reply, SIGNAL(readChannelFinished()), this,
             SIGNAL(readChannelFinished()) );

    connect( m_reply, SIGNAL(readyRead()),
             this, SIGNAL(readyRead()) );

}
