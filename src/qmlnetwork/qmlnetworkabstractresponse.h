#ifndef QMLNETWORKABSTRACTRESPONSE_H
#define QMLNETWORKABSTRACTRESPONSE_H

#include <QObject>
#include <QJsonArray>
#include <QVariant>
#include <QNetworkReply>

#include "qmlnetworkrequest.h"

class QmlNetworkAbstractResponse : public QObject
{
    Q_OBJECT
public:

    explicit QmlNetworkAbstractResponse(QObject *parent = 0);

    virtual ~QmlNetworkAbstractResponse();

    enum NetworkError {
        NoError = QNetworkReply::NoError,

        // network layer errors [relating to the destination server] (1-99):
        ConnectionRefusedError = QNetworkReply::ConnectionRefusedError,
        RemoteHostClosedError = QNetworkReply::RemoteHostClosedError,
        HostNotFoundError = QNetworkReply::HostNotFoundError,
        TimeoutError = QNetworkReply::TimeoutError,
        OperationCanceledError = QNetworkReply::OperationCanceledError,
        SslHandshakeFailedError = QNetworkReply::SslHandshakeFailedError,
        TemporaryNetworkFailureError = QNetworkReply::TemporaryNetworkFailureError,
        NetworkSessionFailedError = QNetworkReply::NetworkSessionFailedError,
        BackgroundRequestNotAllowedError = QNetworkReply::BackgroundRequestNotAllowedError,
        UnknownNetworkError = QNetworkReply::UnknownNetworkError,

        // proxy errors (101-199):
        ProxyConnectionRefusedError = QNetworkReply::ProxyConnectionRefusedError,
        ProxyConnectionClosedError = QNetworkReply::ProxyConnectionClosedError,
        ProxyNotFoundError = QNetworkReply::ProxyNotFoundError,
        ProxyTimeoutError = QNetworkReply::ProxyTimeoutError,
        ProxyAuthenticationRequiredError = QNetworkReply::ProxyAuthenticationRequiredError,
        UnknownProxyError = QNetworkReply::UnknownProxyError,

        // content errors (201-299):
        ContentAccessDenied = QNetworkReply::ContentAccessDenied,
        ContentOperationNotPermittedError = QNetworkReply::ContentOperationNotPermittedError,
        ContentNotFoundError = QNetworkReply::ContentNotFoundError,
        AuthenticationRequiredError = QNetworkReply::AuthenticationRequiredError,
        ContentReSendError = QNetworkReply::ContentReSendError,
        ContentConflictError = QNetworkReply::ContentConflictError,
        ContentGoneError = QNetworkReply::ContentGoneError,
        UnknownContentError = QNetworkReply::UnknownContentError,

        // protocol errors
        ProtocolUnknownError = QNetworkReply::ProtocolUnknownError,
        ProtocolInvalidOperationError = QNetworkReply::ProtocolInvalidOperationError,
        ProtocolFailure = QNetworkReply::ProtocolFailure,

        // Server side errors (401-499)
        InternalServerError = QNetworkReply::InternalServerError,
        OperationNotImplementedError = QNetworkReply::OperationNotImplementedError,
        ServiceUnavailableError = QNetworkReply::ServiceUnavailableError,
        UnknownServerError = QNetworkReply::UnknownServerError
    };
    Q_ENUM(NetworkError)

    QNetworkReply *reply() const;

    void setReply(QNetworkReply *reply);

    Q_INVOKABLE QVariant header(QmlNetworkRequest::KnownHeaders header) const;

    Q_INVOKABLE QVariant getResponseHeader(const QByteArray &headerName) const;

    Q_INVOKABLE QJsonArray getAllResponseHeaders() const;

    /**
      data format:
      [
         {
            "header": "Content-Type",
            "value": "text/html"
         },
         {
            "header": "Via",
            "value": "10.67.15.48"
         }
      ]
     */
    Q_INVOKABLE QJsonArray getAllResponseHeaderPairs() const;

    Q_INVOKABLE bool isRunning() const;

    Q_INVOKABLE bool isFinished() const;

    // Q_INVOKABLE qint64 contentLength() const;

public Q_SLOTS:
    void abort();
    void ignoreSslErrors();

protected Q_SLOTS:
    //! 重写这里
    virtual void onReplyFinished() = 0;

Q_SIGNALS:
    void finished();
    void replyChanged();
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void encrypted();
    void error(QNetworkReply::NetworkError code);
    void metaDataChanged();
    void preSharedKeyAuthenticationRequired(QSslPreSharedKeyAuthenticator * authenticator);
    void sslErrors(const QList<QSslError> & errors);
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void aboutToClose();
    void bytesWritten(qint64 bytes);
    void readChannelFinished();
    void readyRead();

protected:
    void clearOldReplyConnect();
    void connectReplyObject();

private:
    QNetworkReply* m_reply;
};

#endif // QMLNETWORKABSTRACTRESPONSE_H
