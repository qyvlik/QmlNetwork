#ifndef QMLFILEIO_H
#define QMLFILEIO_H

#include "qmliodevice.h"

#include <QFile>

class QmlFileIO : public QmlIODevice
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged FINAL)
    Q_PROPERTY(bool exists READ exists NOTIFY existsChanged FINAL)
    Q_PROPERTY(Permissions permissions READ permissions NOTIFY permissionsChanged FINAL)

public:
    enum FileError {
        NoError = QFile::NoError,
        ReadError = QFile::ReadError,
        WriteError = QFile::WriteError,
        FatalError = QFile::FatalError,
        ResourceError = QFile::ResourceError,
        OpenError = QFile::OpenError,
        AbortError = QFile::AbortError,
        TimeOutError = QFile::TimeOutError,
        UnspecifiedError = QFile::UnspecifiedError,
        RemoveError = QFile::RemoveError,
        RenameError = QFile::RenameError,
        PositionError = QFile::PositionError,
        ResizeError = QFile::ResizeError,
        PermissionsError = QFile::PermissionsError,
        CopyError = QFile::CopyError
    };

    enum Permission {
        ReadOwner = QFile::ReadOwner,
        WriteOwner = QFile::WriteOwner,
        ExeOwner = QFile::ExeOwner,
        ReadUser  = QFile::ReadUser,
        WriteUser  = QFile::WriteUser,
        ExeUser  = QFile::ExeUser,
        ReadGroup = QFile::ReadGroup,
        WriteGroup = QFile::WriteGroup,
        ExeGroup = QFile::ExeGroup,
        ReadOther = QFile::ReadOther,
        WriteOther = QFile::WriteOther,
        ExeOther = QFile::ExeOther
    };

//    typedef QFile::Permission Permission;
    Q_ENUM(Permission)
    Q_DECLARE_FLAGS(Permissions, Permission)
    Q_FLAG(Permissions)

    explicit QmlFileIO(QObject *parent = 0);

    Q_INVOKABLE bool copy(const QString& newName);

    QFile* fileDevice() const;

    QString fileName() const;

    bool flush();

    void setFileName(const QString& filename);

    Q_INVOKABLE FileError error() const;

    Q_INVOKABLE void unsetError();

    Q_INVOKABLE bool exists() const;

    int	handle() const;

    Q_INVOKABLE bool rename(const QString & newName);

    Q_INVOKABLE bool remove();

    Q_INVOKABLE bool resize(qint64 sz);

    Permissions permissions() const;

    Q_INVOKABLE bool setPermissions(Permissions permissions);

Q_SIGNALS:
    void permissionsChanged();
    void fileNameChanged(const QString& filename);
    void existsChanged();

protected:
    void setFileDecice(QFile* file);

public Q_SLOTS:
};

#endif // QMLFILEIO_H
