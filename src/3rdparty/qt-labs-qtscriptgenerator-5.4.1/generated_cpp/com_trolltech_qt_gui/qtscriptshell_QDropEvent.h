#ifndef QTSCRIPTSHELL_QDROPEVENT_H
#define QTSCRIPTSHELL_QDROPEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDropEvent : public QDropEvent
{
public:
    QtScriptShell_QDropEvent(const QPointF&  pos, Qt::DropActions  actions, const QMimeData*  data, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, QEvent::Type  type = QEvent::Drop);
    ~QtScriptShell_QDropEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDROPEVENT_H
