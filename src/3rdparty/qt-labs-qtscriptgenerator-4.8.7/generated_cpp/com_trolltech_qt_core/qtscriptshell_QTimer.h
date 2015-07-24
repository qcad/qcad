#ifndef QTSCRIPTSHELL_QTIMER_H
#define QTSCRIPTSHELL_QTIMER_H

#include <qtimer.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTimer : public QTimer
{
public:
    QtScriptShell_QTimer(QObject*  parent = 0);
    ~QtScriptShell_QTimer();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTIMER_H
