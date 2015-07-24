#ifndef QTSCRIPTSHELL_QDRAGMOVEEVENT_H
#define QTSCRIPTSHELL_QDRAGMOVEEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDragMoveEvent : public QDragMoveEvent
{
public:
    QtScriptShell_QDragMoveEvent(const QPoint&  pos, Qt::DropActions  actions, const QMimeData*  data, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, QEvent::Type  type = QEvent::DragMove);
    ~QtScriptShell_QDragMoveEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDRAGMOVEEVENT_H
