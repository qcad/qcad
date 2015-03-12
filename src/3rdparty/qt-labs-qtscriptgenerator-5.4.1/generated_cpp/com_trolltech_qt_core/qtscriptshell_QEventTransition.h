#ifndef QTSCRIPTSHELL_QEVENTTRANSITION_H
#define QTSCRIPTSHELL_QEVENTTRANSITION_H

#include <qeventtransition.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QEventTransition : public QEventTransition
{
public:
    QtScriptShell_QEventTransition(QObject*  object, QEvent::Type  type, QState*  sourceState = 0);
    QtScriptShell_QEventTransition(QState*  sourceState = 0);
    ~QtScriptShell_QEventTransition();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QEVENTTRANSITION_H
