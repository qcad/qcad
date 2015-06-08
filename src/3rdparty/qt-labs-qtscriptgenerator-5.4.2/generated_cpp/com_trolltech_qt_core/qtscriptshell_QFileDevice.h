#ifndef QTSCRIPTSHELL_QFILEDEVICE_H
#define QTSCRIPTSHELL_QFILEDEVICE_H

#include <qfiledevice.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFileDevice : public QFileDevice
{
public:
    QtScriptShell_QFileDevice();
    QtScriptShell_QFileDevice(QObject*  parent);
    ~QtScriptShell_QFileDevice();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  arg__1);
    void close();
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QString  fileName() const;
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  mode);
    QFileDevice::Permissions  permissions() const;
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  resize(qint64  sz);
    bool  seek(qint64  offset);
    bool  setPermissions(QFileDevice::Permissions  permissionSpec);
    qint64  size() const;
    void timerEvent(QTimerEvent*  arg__1);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFILEDEVICE_H
