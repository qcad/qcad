#ifndef QTSCRIPTSHELL_QBUFFER_H
#define QTSCRIPTSHELL_QBUFFER_H

#include <qbuffer.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QBuffer : public QBuffer
{
public:
    QtScriptShell_QBuffer(QByteArray*  buf, QObject*  parent = 0);
    QtScriptShell_QBuffer(QObject*  parent = 0);
    ~QtScriptShell_QBuffer();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  arg__1);
    void close();
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  openMode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  off);
    qint64  size() const;
    void timerEvent(QTimerEvent*  arg__1);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBUFFER_H
