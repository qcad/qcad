#ifndef QTSCRIPTSHELL_QHTTP_H
#define QTSCRIPTSHELL_QHTTP_H

#include <qhttp.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QHttp : public QHttp
{
public:
    QtScriptShell_QHttp(QObject*  parent = 0);
    QtScriptShell_QHttp(const QString&  hostname, QHttp::ConnectionMode  mode, unsigned short  port = 0, QObject*  parent = 0);
    QtScriptShell_QHttp(const QString&  hostname, unsigned short  port = 80, QObject*  parent = 0);
    ~QtScriptShell_QHttp();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHTTP_H
