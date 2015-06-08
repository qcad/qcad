#ifndef QTSCRIPTSHELL_QTEMPORARYFILE_H
#define QTSCRIPTSHELL_QTEMPORARYFILE_H

#include <qtemporaryfile.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTemporaryFile : public QTemporaryFile
{
public:
    QtScriptShell_QTemporaryFile();
    QtScriptShell_QTemporaryFile(QObject*  parent);
    QtScriptShell_QTemporaryFile(const QString&  templateName);
    QtScriptShell_QTemporaryFile(const QString&  templateName, QObject*  parent);
    ~QtScriptShell_QTemporaryFile();

    bool  atEnd() const;
    qint64  bytesAvailable() const;
    qint64  bytesToWrite() const;
    bool  canReadLine() const;
    void childEvent(QChildEvent*  arg__1);
    void close();
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QAbstractFileEngine*  fileEngine() const;
    bool  isSequential() const;
    bool  open(QIODevice::OpenMode  flags);
    qint64  pos() const;
    qint64  readData(char*  data, qint64  maxlen);
    qint64  readLineData(char*  data, qint64  maxlen);
    bool  reset();
    bool  seek(qint64  offset);
    qint64  size() const;
    void timerEvent(QTimerEvent*  arg__1);
    bool  waitForBytesWritten(int  msecs);
    bool  waitForReadyRead(int  msecs);
    qint64  writeData(const char*  data, qint64  len);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEMPORARYFILE_H
