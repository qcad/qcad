#ifndef QTSCRIPTSHELL_QEVENTLOOP_H
#define QTSCRIPTSHELL_QEVENTLOOP_H

#include <qeventloop.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QEventLoop : public QEventLoop
{
public:
    QtScriptShell_QEventLoop(QObject*  parent = 0);
    ~QtScriptShell_QEventLoop();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QEVENTLOOP_H
