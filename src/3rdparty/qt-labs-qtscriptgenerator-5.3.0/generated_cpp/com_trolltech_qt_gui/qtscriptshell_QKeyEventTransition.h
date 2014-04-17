#ifndef QTSCRIPTSHELL_QKEYEVENTTRANSITION_H
#define QTSCRIPTSHELL_QKEYEVENTTRANSITION_H

#include <qkeyeventtransition.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QKeyEventTransition : public QKeyEventTransition
{
public:
    QtScriptShell_QKeyEventTransition(QObject*  object, QEvent::Type  type, int  key, QState*  sourceState = 0);
    QtScriptShell_QKeyEventTransition(QState*  sourceState = 0);
    ~QtScriptShell_QKeyEventTransition();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QKEYEVENTTRANSITION_H
