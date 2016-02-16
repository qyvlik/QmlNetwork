#include "qmlnetworkresponse.h"

#include <QJsonValue>
#include <QJsonObject>
#include <QVariant>

#include <QDebug>

QmlNetworkResponse::QmlNetworkResponse(QObject *parent)
    : QmlNetworkAbstractResponse(parent)
{
    connect( this, SIGNAL(finished()),
             // onReplyFinished virtual !
             this, SLOT(onReplyFinished()) );
}

QmlNetworkResponse::~QmlNetworkResponse()
{
//    if(m_reply != Q_NULLPTR) {
//        m_reply->deleteLater();
//    }
}

void QmlNetworkResponse::onReplyFinished()
{
    this->setResponseContent(this->reply()->readAll());
}

QByteArray QmlNetworkResponse::responseContent() const
{
    return m_responseContent;
}

void QmlNetworkResponse::setResponseContent(const QByteArray &responseContent)
{
   if(m_responseContent != responseContent) {
       m_responseContent = responseContent;
       Q_EMIT responseContentChanged();
   }
}

