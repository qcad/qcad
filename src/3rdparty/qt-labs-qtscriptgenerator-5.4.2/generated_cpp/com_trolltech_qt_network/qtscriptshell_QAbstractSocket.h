#ifndef QTSCRIPTSHELL_QABSTRACTSOCKET_H
#define QTSCRIPTSHELL_QABSTRACTSOCKET_H

#include <qabstractsocket.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAbstractSocket : public QAbstractSocket
{
public:
    QtScriptShell_QAbstractSocket(QAbstractSocket::SocketType  socketType, QObject*  parent);
    ~QtScriptShell_QAbstractSocket();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  arg__1);
    void close();
    void connectToHost(const QHostAddress&  address, unsigned short  port, QIODevice::OpenMode  mode = ReadWrite);
    void connectToHost(const QString&  hostName, unsigned short  port, QIODevice::OpenMode  mode = ReadWrite, QAbstractSocket::NetworkLayerProtocol  protocol = QAbstractSocket::AnyIPProtocol);
    void customEvent(QEvent*  arg__1);
    void disconnectFromHost();
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  mode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    void resume();
    bool  seek(qint64  pos);
    void setReadBufferSize(qint64  size);
    void setSocketOption(QAbstractSocket::SocketOption  option, const QVariant&  value);
    qint64  size() const;
    QVariant  socketOption(QAbstractSocket::SocketOption  option);
    void timerEvent(QTimerEvent*  arg__1);
    bool  waitForBytesWritten(int  msecs = 30000);
    bool  waitForConnected(int  msecs = 30000);
    bool  waitForDisconnected(int  msecs = 30000);
    bool  waitForReadyRead(int  msecs = 30000);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTSOCKET_H
