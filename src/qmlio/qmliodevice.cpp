#include "qmliodevice.h"

QmlIODevice::QmlIODevice(QObject *parent)
    : QObject(parent),
      m_device(Q_NULLPTR)
{

}

QIODevice *QmlIODevice::device() const
{
    return m_device;
}

/*
    void aboutToClose();
    void bytesWritten(qint64 bytes);
    void readChannelFinished();
    void readyRead();
*/

void QmlIODevice::setDevice(QIODevice *io)
{
    if(m_device != io) {

        //! 如果 m_device 被删除了怎么办？
        if(m_device != Q_NULLPTR) {
           disconnect(m_device, 0, this, 0);
        }

        m_device = io;

        if(m_device != Q_NULLPTR) {
            connect( m_device,SIGNAL(aboutToClose()),
                     this, SIGNAL(aboutToClose()) );

            connect( m_device, SIGNAL(bytesWritten(qint64)),
                     this, SIGNAL(bytesWritten(qint64)) );

            connect( m_device, SIGNAL(readChannelFinished()),
                     this, SIGNAL(readChannelFinished()) );

            connect( m_device, SIGNAL(readyRead()),
                     this, SIGNAL(readyRead()) );
        }

        emit deviceChanged();
        emit hasDeviceChanged(this->hasDevice());
    }
}

bool QmlIODevice::hasDevice() const
{
    return m_device != Q_NULLPTR;
}

bool QmlIODevice::atEnd() const
{
    return this->hasDevice()
            ? this->m_device->atEnd()
            : false;
}

qint64 QmlIODevice::bytesAvailable() const
{
    return this->hasDevice()
            ? this->m_device->bytesAvailable()
            : -1;
}

qint64 QmlIODevice::bytesToWrite() const
{
    return this->hasDevice()
            ? this->m_device->bytesToWrite()
            : -1;
}

bool QmlIODevice::canReadLine() const
{
    return this->hasDevice()
            ? this->m_device->canReadLine()
            : false;
}

bool QmlIODevice::close()
{
    return this->hasDevice()
            ? (this->m_device->close(), true)
            : false;
}

QString QmlIODevice::errorString() const
{
    return this->hasDevice()
            ? this->m_device->errorString()
            : "";
}

bool QmlIODevice::isOpen() const
{
    return this->hasDevice()
            ? this->m_device->isOpen()
            : false;
}

QJSValue QmlIODevice::getChar()
{
    if(this->hasDevice()){
        char c = 0;
        if(this->m_device->getChar(&c)){
            return QJSValue(QString(QChar(c)));
        } else {
            return QJSValue();
        }
    } else {
        return QJSValue();
    }
}

bool QmlIODevice::isReadable() const
{
    return this->hasDevice()
            ? this->m_device->isReadable()
            : false;
}

bool QmlIODevice::isSequential() const
{
    return this->hasDevice()
            ? this->m_device->isSequential()
            : false;
}

bool QmlIODevice::isTextModeEnabled() const
{
    return this->hasDevice()
            ? this->m_device->isTextModeEnabled()
            : false;
}

void QmlIODevice::setTextModeEnabled(bool enabled)
{
    if(this->hasDevice()) {
        this->m_device->setTextModeEnabled(enabled);
        emit isTextModeEnabledChanged(enabled);
    }
}

bool QmlIODevice::isWritable() const
{
    return this->hasDevice()
            ? this->m_device->isWritable()
            : false;
}

QByteArray QmlIODevice::peek(qint64 maxSize)
{
    return this->hasDevice()
            ? this->m_device->peek(maxSize)
            : "";
}

qint64 QmlIODevice::pos() const
{
    return this->hasDevice()
            ? this->m_device->pos()
            : -1;
}

bool QmlIODevice::putChar(char c)
{
    return this->hasDevice()
            ? this->m_device->putChar(c)
            : false;
}

QByteArray QmlIODevice::read(qint64 maxSize)
{
    return this->hasDevice()
            ? this->m_device->read(maxSize)
            : "";
}

QByteArray QmlIODevice::readAll()
{
    return this->hasDevice()
            ? this->m_device->readAll()
            : "";
}

QByteArray QmlIODevice::readLine(qint64 maxSize)
{
    return this->hasDevice()
            ? this->m_device->readLine(maxSize)
            : "";
}

bool QmlIODevice::reset()
{
    return this->hasDevice()
            ? this->reset()
            : false;
}

bool QmlIODevice::seek(qint64 pos)
{
    return this->hasDevice()
            ? this->m_device->seek(pos)
            : false;
}

qint64 QmlIODevice::size() const
{
    return this->hasDevice()
            ? this->m_device->size()
            : -1;
}

bool QmlIODevice::ungetChar(char c)
{
    return this->hasDevice()
            ? ( this->m_device->ungetChar(c), false)
            : false;
}

bool QmlIODevice::waitForBytesWritten(int msecs)
{
    return this->hasDevice()
            ? this->m_device->waitForBytesWritten(msecs)
            : false;
}

bool QmlIODevice::waitForReadyRead(int msecs)
{
    return this->hasDevice()
            ? this->m_device->waitForReadyRead(msecs)
            : false;
}

qint64 QmlIODevice::write(const QByteArray &byteArray)
{
    return this->hasDevice()
            ? this->m_device->write(byteArray)
            : -1;
}

bool QmlIODevice::open(OpenMode mode)
{
    return this->hasDevice()
            ? this->m_device->open(QIODevice::OpenMode(QFlag((OpenMode::Int)mode)))
            : false;
}

QmlIODevice::OpenMode QmlIODevice::openMode() const
{
    return this->hasDevice()
            ? OpenMode(QFlag((QIODevice::OpenMode::Int)this->m_device->openMode()))
            : QmlIODevice::NotOpen;
}

void QmlIODevice::onDeviceChanged()
{

}

