#include "qmlbuffer.h"

#include <QBuffer>
#include <QDebug>

QmlBuffer::QmlBuffer(QObject *parent)
    : QmlIODevice(parent)
{
    this->setBuffer(new QBuffer(this));
}

QByteArray QmlBuffer::data() const
{
    return this->buffer()->data();
}

void QmlBuffer::setData(const QByteArray &data)
{
    if(this->buffer()->data() != data) {
        //! Does nothing if isOpen() is true.
        this->buffer()->setData(data);
        Q_EMIT dataChanged();
    }
}

QBuffer *QmlBuffer::buffer() const
{
    return (QBuffer*)this->device();
}

void QmlBuffer::setBuffer(QBuffer *buffer)
{
    // buffer->open(QBuffer::ReadWrite);
    this->setDevice(buffer);
}

