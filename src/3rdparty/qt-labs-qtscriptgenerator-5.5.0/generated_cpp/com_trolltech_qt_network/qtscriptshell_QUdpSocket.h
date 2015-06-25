#ifndef QTSCRIPTSHELL_QUDPSOCKET_H
#define QTSCRIPTSHELL_QUDPSOCKET_H

#include <qudpsocket.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QUdpSocket : public QUdpSocket
{
public:
    QtScriptShell_QUdpSocket(QObject*  parent = 0);
    ~QtScriptShell_QUdpSocket();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  arg__1);
    void close();
    void connectToHost(const QHostAddress&  address, unsigned short  port, QIODevice::OpenMode  mode);
    void connectToHost(const QString&  hostName, unsigned short  port, QIODevice::OpenMode  mode, QAbstractSocket::NetworkLayerProtocol  protocol);
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
    bool  waitForBytesWritten(int  msecs);
    bool  waitForConnected(int  msecs);
    bool  waitForDisconnected(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUDPSOCKET_H
