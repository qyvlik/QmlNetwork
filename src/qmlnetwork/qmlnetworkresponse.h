#ifndef QMLNETWORKRESPONSE_H
#define QMLNETWORKRESPONSE_H

#include <QObject>
#include <QSslError>
#include <QNetworkReply>
#include <QJsonArray>

#include "qmlnetworkabstractresponse.h"

class QVariant;

class QmlNetworkResponse : public QmlNetworkAbstractResponse
{
    Q_OBJECT
    Q_PROPERTY(QByteArray responseContent READ responseContent NOTIFY responseContentChanged FINAL)

public:
    explicit QmlNetworkResponse(QObject *parent = 0);
    ~QmlNetworkResponse();

    QByteArray responseContent() const;

protected:
    void setResponseContent(const QByteArray &responseContent);

protected Q_SLOTS:
    //! 重写这里
    void onReplyFinished();

Q_SIGNALS:
    void responseContentChanged();

private:
    QByteArray m_responseContent;
};

#endif // QMLNETWORKRESPONSE_H
