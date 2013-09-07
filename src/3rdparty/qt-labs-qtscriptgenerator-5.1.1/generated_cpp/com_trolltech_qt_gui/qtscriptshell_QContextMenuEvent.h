#ifndef QTSCRIPTSHELL_QCONTEXTMENUEVENT_H
#define QTSCRIPTSHELL_QCONTEXTMENUEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QContextMenuEvent : public QContextMenuEvent
{
public:
    QtScriptShell_QContextMenuEvent(QContextMenuEvent::Reason  reason, const QPoint&  pos);
    QtScriptShell_QContextMenuEvent(QContextMenuEvent::Reason  reason, const QPoint&  pos, const QPoint&  globalPos);
    QtScriptShell_QContextMenuEvent(QContextMenuEvent::Reason  reason, const QPoint&  pos, const QPoint&  globalPos, Qt::KeyboardModifiers  modifiers);
    ~QtScriptShell_QContextMenuEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QCONTEXTMENUEVENT_H
