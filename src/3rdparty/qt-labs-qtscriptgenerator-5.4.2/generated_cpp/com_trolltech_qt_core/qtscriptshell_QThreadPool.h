#ifndef QTSCRIPTSHELL_QTHREADPOOL_H
#define QTSCRIPTSHELL_QTHREADPOOL_H

#include <qthreadpool.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QThreadPool : public QThreadPool
{
public:
    QtScriptShell_QThreadPool(QObject*  parent = 0);
    ~QtScriptShell_QThreadPool();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTHREADPOOL_H
