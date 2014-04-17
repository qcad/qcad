#ifndef QTSCRIPTSHELL_QFINALSTATE_H
#define QTSCRIPTSHELL_QFINALSTATE_H

#include <qfinalstate.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFinalState : public QFinalState
{
public:
    QtScriptShell_QFinalState(QState*  parent = 0);
    ~QtScriptShell_QFinalState();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFINALSTATE_H
