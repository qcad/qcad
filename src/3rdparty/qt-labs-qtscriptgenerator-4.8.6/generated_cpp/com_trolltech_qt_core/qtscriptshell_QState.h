#ifndef QTSCRIPTSHELL_QSTATE_H
#define QTSCRIPTSHELL_QSTATE_H

#include <qstate.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QState : public QState
{
public:
    QtScriptShell_QState(QState*  parent = 0);
    QtScriptShell_QState(QState::ChildMode  childMode, QState*  parent = 0);
    ~QtScriptShell_QState();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTATE_H
