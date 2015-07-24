#ifndef QTSCRIPTSHELL_QMOUSEEVENT_H
#define QTSCRIPTSHELL_QMOUSEEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QMouseEvent : public QMouseEvent
{
public:
    QtScriptShell_QMouseEvent(QEvent::Type  type, const QPointF&  localPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers);
    QtScriptShell_QMouseEvent(QEvent::Type  type, const QPointF&  localPos, const QPointF&  screenPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers);
    QtScriptShell_QMouseEvent(QEvent::Type  type, const QPointF&  localPos, const QPointF&  windowPos, const QPointF&  screenPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers);
    ~QtScriptShell_QMouseEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOUSEEVENT_H
