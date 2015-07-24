#ifndef QTSCRIPTSHELL_QSOCKETNOTIFIER_H
#define QTSCRIPTSHELL_QSOCKETNOTIFIER_H

#include <qsocketnotifier.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QSocketNotifier : public QSocketNotifier
{
public:
    QtScriptShell_QSocketNotifier(int  socket, QSocketNotifier::Type  arg__2, QObject*  parent = 0);
    ~QtScriptShell_QSocketNotifier();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSOCKETNOTIFIER_H
