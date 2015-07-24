#ifndef QTSCRIPTSHELL_QMOUSEEVENTTRANSITION_H
#define QTSCRIPTSHELL_QMOUSEEVENTTRANSITION_H

#include <qmouseeventtransition.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QMouseEventTransition : public QMouseEventTransition
{
public:
    QtScriptShell_QMouseEventTransition(QObject*  object, QEvent::Type  type, Qt::MouseButton  button, QState*  sourceState = 0);
    QtScriptShell_QMouseEventTransition(QState*  sourceState = 0);
    ~QtScriptShell_QMouseEventTransition();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOUSEEVENTTRANSITION_H
