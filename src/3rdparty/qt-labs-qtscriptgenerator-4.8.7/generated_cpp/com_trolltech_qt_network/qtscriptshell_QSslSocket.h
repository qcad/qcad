#ifndef QTSCRIPTSHELL_QSSLSOCKET_H
#define QTSCRIPTSHELL_QSSLSOCKET_H

#include <qsslsocket.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSslSocket : public QSslSocket
{
public:
    QtScriptShell_QSslSocket(QObject*  parent = 0);
    ~QtScriptShell_QSslSocket();

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
    bool  open(QIODevice::OpenMode  mode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  pos);
    qint64  size() const;
    void timerEvent(QTimerEvent*  arg__1);
    bool  waitForBytesWritten(int  msecs = 30000);
    bool  waitForReadyRead(int  msecs = 30000);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSSLSOCKET_H
