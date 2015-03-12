#ifndef QTSCRIPTSHELL_QSTATEMACHINE_H
#define QTSCRIPTSHELL_QSTATEMACHINE_H

#include <qstatemachine.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStateMachine : public QStateMachine
{
public:
    QtScriptShell_QStateMachine(QObject*  parent = 0);
    QtScriptShell_QStateMachine(QState::ChildMode  childMode, QObject*  parent = 0);
    ~QtScriptShell_QStateMachine();

    void beginMicrostep(QEvent*  event);
    void beginSelectTransitions(QEvent*  event);
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    void endMicrostep(QEvent*  event);
    void endSelectTransitions(QEvent*  event);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  watched, QEvent*  event);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTATEMACHINE_H
