#include "qmlnetworkrequest.h"
#include "../qmlio/qmliodevice.h"

QmlNetworkRequest::QmlNetworkRequest(QObject *parent)
    : QObject(parent),
      m_ioDevice(Q_NULLPTR)
{
    connect( this, SIGNAL(requestChanged()), this, SLOT(onRequestChanged()) );
}

void QmlNetworkRequest::clear()
{
    this->setRequest(QNetworkRequest());
    Q_EMIT this->urlChanged(QUrl());
}

void QmlNetworkRequest::setHeader(QmlNetworkRequest::KnownHeaders header, const QVariant &value)
{
    m_request.setHeader((QNetworkRequest::KnownHeaders)header, value);
}

bool QmlNetworkRequest::hasRawHeader(const QByteArray &headerName) const
{
    return m_request.hasRawHeader(headerName);
}

QNetworkRequest QmlNetworkRequest::request() const
{
    return m_request;
}

void QmlNetworkRequest::setRequest(const QNetworkRequest &request)
{
    if(m_request != request) {
        m_request = request;
        Q_EMIT requestChanged();
    }
}

QUrl QmlNetworkRequest::url() const
{
    return m_request.url();
}

void QmlNetworkRequest::setUrl(const QUrl &url)
{
    if(m_request.url() != url) {
        m_request.setUrl(url);
        Q_EMIT urlChanged(m_request.url());
    }
}


QmlNetworkRequest::Priority QmlNetworkRequest::priority() const
{
    return (QmlNetworkRequest::Priority)m_request.priority();
}


void QmlNetworkRequest::setPriority(const QmlNetworkRequest::Priority &priority)
{
    if(m_request.priority() != (QNetworkRequest::Priority)priority) {
        m_request.setPriority((QNetworkRequest::Priority)priority);
        Q_EMIT priorityChanged();
    }
}


QList<QByteArray> QmlNetworkRequest::rawHeaderList() const
{
    return m_request.rawHeaderList();
}


void QmlNetworkRequest::setRawHeader(const QByteArray &headerName, const QByteArray &headerValue)
{
    m_request.setRawHeader(headerName, headerValue);
}

void QmlNetworkRequest::onRequestChanged()
{
    Q_EMIT urlChanged(this->url());
    // other
}

QmlIODevice *QmlNetworkRequest::ioDevice() const
{
    return m_ioDevice;
}

void QmlNetworkRequest::setIoDevice(QmlIODevice *ioDevice)
{
    if(m_ioDevice != ioDevice) {
        m_ioDevice = ioDevice;
        Q_EMIT ioDeviceChanged();
    }
}

QByteArray QmlNetworkRequest::rawHeader(const QByteArray &headerName) const
{
    return m_request.rawHeader(headerName);
}

QSslConfiguration QmlNetworkRequest::sslConfiguration() const
{
    return m_request.sslConfiguration();
}

void QmlNetworkRequest::setSslConfiguration(const QSslConfiguration &value)
{
    if(m_request.sslConfiguration() != value) {
        m_request.setSslConfiguration(value);
        Q_EMIT sslConfigurationChanged();
    }
}

