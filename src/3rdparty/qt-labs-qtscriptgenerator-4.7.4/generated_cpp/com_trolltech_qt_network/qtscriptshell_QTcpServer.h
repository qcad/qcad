#ifndef QTSCRIPTSHELL_QTCPSERVER_H
#define QTSCRIPTSHELL_QTCPSERVER_H

#include <qtcpserver.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTcpServer : public QTcpServer
{
public:
    QtScriptShell_QTcpServer(QObject*  parent = 0);
    ~QtScriptShell_QTcpServer();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  hasPendingConnections() const;
    void incomingConnection(int  handle);
    QTcpSocket*  nextPendingConnection();
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTCPSERVER_H
