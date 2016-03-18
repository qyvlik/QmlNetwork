#include "qmlfileio.h"

#include <QDebug>

QmlFileIO::QmlFileIO(QObject *parent)
    : QmlIODevice(parent)
{
    qRegisterMetaType<FileError>("QmlFileIO::FileError");
    qRegisterMetaType<Permission>("QmlFileIO::Permission");
    qRegisterMetaType<Permissions>("QmlFileIO::Permissions");

    this->setDevice(new QFile(this));
}

QFile *QmlFileIO::fileDevice() const
{
    return (QFile*)this->device();
}

QString QmlFileIO::fileName() const
{
    return this->fileDevice()->fileName();
}

bool QmlFileIO::flush()
{
    return this->fileDevice()->flush();
}

void QmlFileIO::setFileName(const QString &filename)
{
    if(this->fileDevice()->fileName() != filename) {
        this->fileDevice()->setFileName(filename);
        Q_EMIT fileNameChanged(this->fileName());
        Q_EMIT existsChanged();
    }
}

QmlFileIO::FileError QmlFileIO::error() const
{
    return (QmlFileIO::FileError)this->fileDevice()->error();
}

void QmlFileIO::unsetError()
{
    this->fileDevice()->unsetError();
}

bool QmlFileIO::exists() const
{
    return this->fileDevice()->exists();
}

int QmlFileIO::handle() const
{
    return this->fileDevice()->handle();
}

bool QmlFileIO::copy(const QString &newName)
{
    //! The source file is closed before it is copied.
    return this->fileDevice()->copy(newName);
}

bool QmlFileIO::rename(const QString &newName)
{
    return this->fileDevice()->rename(newName);
}

bool QmlFileIO::remove()
{
    //! The file is closed before it is removed.
#ifdef QT_DEBUG
    qDebug() << Q_FUNC_INFO << ": " << this->fileName() << endl;
#endif
    return this->fileDevice()->remove();
}

bool QmlFileIO::resize(qint64 sz)
{
    return this->fileDevice()->resize(sz);
}

QmlFileIO::Permissions QmlFileIO::permissions() const
{
    return Permissions(QFlag((QFile::Permissions::Int)fileDevice()->permissions()));
}

bool QmlFileIO::setPermissions(Permissions permissions)
{

    if(fileDevice()->setPermissions(QFileDevice::Permissions(
                                        QFlag((Permissions::Int)permissions))))
    {
        Q_EMIT permissionsChanged();
        return true;
    }
    else
    {
        return false;
    }
}

