#ifndef QTSCRIPTSHELL_QCHILDEVENT_H
#define QTSCRIPTSHELL_QCHILDEVENT_H

#include <qcoreevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QChildEvent : public QChildEvent
{
public:
    QtScriptShell_QChildEvent(QEvent::Type  type, QObject*  child);
    ~QtScriptShell_QChildEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCHILDEVENT_H
