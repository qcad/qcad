#ifndef QTSCRIPTSHELL_QABSTRACTSTATE_H
#define QTSCRIPTSHELL_QABSTRACTSTATE_H

#include <qabstractstate.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractState : public QAbstractState
{
public:
    QtScriptShell_QAbstractState(QState*  parent = 0);
    ~QtScriptShell_QAbstractState();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void onEntry(QEvent*  event);
    void onExit(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTSTATE_H
