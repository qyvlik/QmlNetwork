#ifndef QMLBUFFER_H
#define QMLBUFFER_H

#include "qmliodevice.h"

class QBuffer;

class QmlBuffer : public QmlIODevice
{
    Q_OBJECT
    Q_PROPERTY(QByteArray data READ data WRITE setData NOTIFY dataChanged)

public:
    explicit
    QmlBuffer(QObject *parent = 0);

    QByteArray data() const;
    void setData(const QByteArray& data);

    QBuffer* buffer() const;

protected:
    void setBuffer(QBuffer* buffer);

Q_SIGNALS:
    void dataChanged();
};

#endif // QMLBUFFER_H
