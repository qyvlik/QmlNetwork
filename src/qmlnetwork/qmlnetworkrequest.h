#ifndef QMLNETWORKREQUEST_H
#define QMLNETWORKREQUEST_H

#include <QObject>
#include <QUrl>
#include <QNetworkRequest>
#include <QByteArray>
#include <QList>
#include <QSslConfiguration>
#include <QIODevice>

#include <QDebug>

class QmlIODevice;

class QmlNetworkRequest : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(Priority priority READ priority WRITE setPriority NOTIFY priorityChanged)
    Q_PROPERTY(QmlIODevice* ioDevice READ ioDevice WRITE setIoDevice NOTIFY ioDeviceChanged)

public:
    enum Attribute {
        HttpStatusCodeAttribute = QNetworkRequest::HttpStatusCodeAttribute,
        HttpReasonPhraseAttribute = QNetworkRequest::HttpReasonPhraseAttribute,
        RedirectionTargetAttribute = QNetworkRequest::RedirectionTargetAttribute,
        ConnectionEncryptedAttribute = QNetworkRequest::ConnectionEncryptedAttribute,
        CacheLoadControlAttribute = QNetworkRequest::CacheLoadControlAttribute,
        CacheSaveControlAttribute = QNetworkRequest::CacheSaveControlAttribute,
        SourceIsFromCacheAttribute = QNetworkRequest::SourceIsFromCacheAttribute,
        DoNotBufferUploadDataAttribute = QNetworkRequest::DoNotBufferUploadDataAttribute,
        HttpPipeliningAllowedAttribute = QNetworkRequest::HttpPipeliningAllowedAttribute,
        HttpPipeliningWasUsedAttribute = QNetworkRequest::HttpPipeliningWasUsedAttribute,
        CustomVerbAttribute = QNetworkRequest::CustomVerbAttribute,
        CookieLoadControlAttribute = QNetworkRequest::CookieLoadControlAttribute,
        AuthenticationReuseAttribute = QNetworkRequest::AuthenticationReuseAttribute,
        CookieSaveControlAttribute = QNetworkRequest::CookieSaveControlAttribute,
        MaximumDownloadBufferSizeAttribute = QNetworkRequest::MaximumDownloadBufferSizeAttribute,
        DownloadBufferAttribute = QNetworkRequest::DownloadBufferAttribute,
        SynchronousRequestAttribute = QNetworkRequest::SynchronousRequestAttribute,
        BackgroundRequestAttribute = QNetworkRequest::BackgroundRequestAttribute,
        SpdyAllowedAttribute = QNetworkRequest::SpdyAllowedAttribute,
        SpdyWasUsedAttribute = QNetworkRequest::SpdyWasUsedAttribute,
        EmitAllUploadProgressSignalsAttribute = QNetworkRequest::EmitAllUploadProgressSignalsAttribute,

        User = QNetworkRequest::User,
        UserMax = QNetworkRequest::UserMax
    };
    Q_ENUM(Attribute)

    enum KnownHeaders {
        ContentTypeHeader = QNetworkRequest::ContentTypeHeader,
        ContentLengthHeader = QNetworkRequest::ContentLengthHeader,
        LocationHeader = QNetworkRequest::LocationHeader,
        LastModifiedHeader = QNetworkRequest::LastModifiedHeader,
        CookieHeader = QNetworkRequest::CookieHeader,
        SetCookieHeader = QNetworkRequest::SetCookieHeader,
        ContentDispositionHeader = QNetworkRequest::ContentDispositionHeader,  // added for QMultipartMessage
        UserAgentHeader = QNetworkRequest::UserAgentHeader,
        ServerHeader = QNetworkRequest::ServerHeader
    };
    Q_ENUM(KnownHeaders)

    enum CacheLoadControl {
        AlwaysNetwork = QNetworkRequest::AlwaysNetwork,
        PreferNetwork = QNetworkRequest::PreferNetwork,
        PreferCache = QNetworkRequest::PreferCache,
        AlwaysCache = QNetworkRequest::AlwaysCache
    };
    Q_ENUM(CacheLoadControl)

    enum LoadControl {
        Automatic = QNetworkRequest::Automatic,
        Manual = QNetworkRequest::Manual
    };
    Q_ENUM(LoadControl)

    enum Priority {
        HighPriority  = QNetworkRequest::HighPriority,
        NormalPriority = QNetworkRequest::NormalPriority,
        LowPriority = QNetworkRequest::LowPriority
    };
    Q_ENUM(Priority)

    explicit QmlNetworkRequest(QObject *parent = 0);

    // Test
//    Q_INVOKABLE void test(KnownHeaders k) {
//        qDebug() << k ;
//    }

    Q_INVOKABLE void clear();

    Q_INVOKABLE void setHeader(KnownHeaders header, const QVariant & value);

    Q_INVOKABLE bool hasRawHeader(const QByteArray & headerName) const;

    QNetworkRequest request() const;

    void setRequest(const QNetworkRequest &request);

    QUrl url() const;

    Priority priority() const;

    Q_INVOKABLE QList<QByteArray> rawHeaderList() const;

    Q_INVOKABLE QByteArray rawHeader(const QByteArray & headerName) const;

    QSslConfiguration sslConfiguration() const;

    void setSslConfiguration(const QSslConfiguration &value);

    QmlIODevice *ioDevice() const;

    void setIoDevice(QmlIODevice *ioDevice);

Q_SIGNALS:
    void ioDeviceChanged();
    void requestChanged();
    void urlChanged(const QUrl& url);
    void priorityChanged();
    void sslConfigurationChanged();

public Q_SLOTS:
    void setUrl(const QUrl &url);
    void setPriority(const Priority &priority);
    void setRawHeader(const QByteArray & headerName, const QByteArray & headerValue);

private slots:
    void onRequestChanged();

private:
    QNetworkRequest m_request;
    QmlIODevice* m_ioDevice;
};

#endif // QMLNETWORKREQUEST_H
