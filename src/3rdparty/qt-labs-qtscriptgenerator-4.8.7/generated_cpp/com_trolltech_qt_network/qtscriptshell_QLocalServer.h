#ifndef QTSCRIPTSHELL_QLOCALSERVER_H
#define QTSCRIPTSHELL_QLOCALSERVER_H

#include <qlocalserver.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QLocalServer : public QLocalServer
{
public:
    QtScriptShell_QLocalServer(QObject*  parent = 0);
    ~QtScriptShell_QLocalServer();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  hasPendingConnections() const;
    void incomingConnection(quintptr  socketDescriptor);
    QLocalSocket*  nextPendingConnection();
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QLOCALSERVER_H
