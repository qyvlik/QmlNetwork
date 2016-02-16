#ifndef QMLIODEVICE_H
#define QMLIODEVICE_H

#include <QObject>
#include <QIODevice>
#include <QJSValue>

// abstract
class QmlIODevice : public QObject
{
    Q_OBJECT
    //    Q_PROPERTY(bool atEnd READ atEnd NOTIFY atEndChanged FINAL)
    //    Q_PROPERTY(qint64 bytesAvailable READ bytesAvailable NOTIFY bytesAvailableChanged FINAL)
    //    Q_PROPERTY(qint64 bytesToWrite READ bytesToWrite NOTIFY bytesToWriteChanged FINAL)
    Q_PROPERTY(bool hasDevice READ hasDevice NOTIFY hasDeviceChanged FINAL)

public:
    enum OpenModeFlag {
        NotOpen = QIODevice::NotOpen,
        ReadOnly = QIODevice::ReadOnly,
        WriteOnly = QIODevice::WriteOnly,
        ReadWrite = QIODevice::ReadWrite,
        Append = QIODevice::Append,
        Truncate = QIODevice::Truncate,
        Text = QIODevice::Text,
        Unbuffered = QIODevice::Unbuffered
    };
    Q_ENUM(OpenModeFlag)
    Q_DECLARE_FLAGS(OpenMode, OpenModeFlag)
    Q_FLAG(OpenMode)

    explicit QmlIODevice(QObject *parent = 0);

    QIODevice* device() const;

    bool hasDevice() const;

    Q_INVOKABLE bool atEnd() const;

    Q_INVOKABLE qint64 bytesAvailable() const;

    Q_INVOKABLE qint64 bytesToWrite() const;

    Q_INVOKABLE bool canReadLine() const;

    Q_INVOKABLE bool close();

    Q_INVOKABLE QString errorString() const;

    Q_INVOKABLE bool isOpen() const;

    Q_INVOKABLE QJSValue getChar();

    Q_INVOKABLE bool isReadable() const;

    Q_INVOKABLE bool isSequential() const;

    Q_INVOKABLE bool isTextModeEnabled() const;

    Q_INVOKABLE void setTextModeEnabled(bool enabled);

    Q_INVOKABLE bool isWritable() const;

    Q_INVOKABLE QByteArray peek(qint64 maxSize);

    Q_INVOKABLE qint64 pos() const;

    Q_INVOKABLE bool putChar(char c);

    Q_INVOKABLE QByteArray read(qint64 maxSize);

    Q_INVOKABLE QByteArray readAll();

    Q_INVOKABLE QByteArray readLine(qint64 maxSize = 0);

    Q_INVOKABLE bool reset();

    Q_INVOKABLE bool seek(qint64 pos);

    Q_INVOKABLE qint64 size() const;

    Q_INVOKABLE bool ungetChar(char c);

    Q_INVOKABLE bool waitForBytesWritten(int msecs);

    Q_INVOKABLE bool waitForReadyRead(int msecs);

    Q_INVOKABLE qint64 write(const QByteArray & byteArray);

    Q_INVOKABLE bool open(OpenMode mode);

    Q_INVOKABLE QmlIODevice::OpenMode openMode() const;

Q_SIGNALS:
    void hasDeviceChanged(bool hasDevice);
    void deviceChanged();
//    void atEndChanged(bool atEnd);
//    void bytesAvailableChanged(qint64 bytesAvailable);
//    void bytesToWriteChanged(qint64 bytesToWrite);
//    void canReadLineChanged(bool canReadLine);
//    void isOpenChanged(bool isOpen);
//    void isReadableChanged(bool isReadable);
//    void isSequentialChanged(bool isSequential);
    void isTextModeEnabledChanged(bool isTextModeEnabled);
//    void isWritableChanged(bool isWritable);

    void aboutToClose();
    void bytesWritten(qint64 bytes);
    void readChannelFinished();
    void readyRead();

protected:
    void setDevice(QIODevice* io);

private Q_SLOTS:
    void onDeviceChanged();

private:
    QIODevice* m_device;
};

#endif // QMLIODEVICE_H
