#ifndef QTSCRIPTSHELL_QDRAGRESPONSEEVENT_H
#define QTSCRIPTSHELL_QDRAGRESPONSEEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDragResponseEvent : public QDragResponseEvent
{
public:
    QtScriptShell_QDragResponseEvent(bool  accepted);
    ~QtScriptShell_QDragResponseEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDRAGRESPONSEEVENT_H
