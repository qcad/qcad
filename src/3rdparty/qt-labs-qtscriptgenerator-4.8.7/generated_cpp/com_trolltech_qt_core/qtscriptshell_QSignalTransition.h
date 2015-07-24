#ifndef QTSCRIPTSHELL_QSIGNALTRANSITION_H
#define QTSCRIPTSHELL_QSIGNALTRANSITION_H

#include <qsignaltransition.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSignalTransition : public QSignalTransition
{
public:
    QtScriptShell_QSignalTransition(QObject*  sender, const char*  signal, QState*  sourceState = 0);
    QtScriptShell_QSignalTransition(QState*  sourceState = 0);
    ~QtScriptShell_QSignalTransition();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  e);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    bool  eventTest(QEvent*  event);
    void onTransition(QEvent*  event);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSIGNALTRANSITION_H
