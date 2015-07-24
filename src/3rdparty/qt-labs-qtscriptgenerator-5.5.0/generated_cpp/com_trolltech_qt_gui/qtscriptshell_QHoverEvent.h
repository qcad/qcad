#ifndef QTSCRIPTSHELL_QHOVEREVENT_H
#define QTSCRIPTSHELL_QHOVEREVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QHoverEvent : public QHoverEvent
{
public:
    QtScriptShell_QHoverEvent(QEvent::Type  type, const QPointF&  pos, const QPointF&  oldPos, Qt::KeyboardModifiers  modifiers = Qt::NoModifier);
    ~QtScriptShell_QHoverEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHOVEREVENT_H
