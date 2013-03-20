#ifndef QTSCRIPTSHELL_QTIMEREVENT_H
#define QTSCRIPTSHELL_QTIMEREVENT_H

#include <qcoreevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTimerEvent : public QTimerEvent
{
public:
    QtScriptShell_QTimerEvent(int  timerId);
    ~QtScriptShell_QTimerEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTIMEREVENT_H
