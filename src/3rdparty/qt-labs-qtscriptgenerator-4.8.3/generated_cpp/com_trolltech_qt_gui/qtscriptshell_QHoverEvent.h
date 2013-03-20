#ifndef QTSCRIPTSHELL_QHOVEREVENT_H
#define QTSCRIPTSHELL_QHOVEREVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QHoverEvent : public QHoverEvent
{
public:
    QtScriptShell_QHoverEvent(QEvent::Type  type, const QPoint&  pos, const QPoint&  oldPos);
    ~QtScriptShell_QHoverEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHOVEREVENT_H
