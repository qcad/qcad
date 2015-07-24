#ifndef QTSCRIPTSHELL_QNETWORKREPLY_H
#define QTSCRIPTSHELL_QNETWORKREPLY_H

#include <qnetworkreply.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QNetworkReply : public QNetworkReply
{
public:
    QtScriptShell_QNetworkReply(QObject*  parent = 0);
    ~QtScriptShell_QNetworkReply();

    void abort();
    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  arg__1);
    void close();
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void ignoreSslErrors();
    void ignoreSslErrorsImplementation(const QList<QSslError >&  arg__1);
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  mode);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  pos);
    void setReadBufferSize(qint64  size);
    void setSslConfigurationImplementation(const QSslConfiguration&  arg__1);
    qint64  size() const;
    void sslConfigurationImplementation(QSslConfiguration&  arg__1) const;
    void timerEvent(QTimerEvent*  arg__1);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKREPLY_H
