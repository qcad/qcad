#ifndef QTSCRIPTSHELL_QMOUSEEVENT_H
#define QTSCRIPTSHELL_QMOUSEEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QMouseEvent : public QMouseEvent
{
public:
    QtScriptShell_QMouseEvent(QEvent::Type  type, const QPoint&  pos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers);
    QtScriptShell_QMouseEvent(QEvent::Type  type, const QPoint&  pos, const QPoint&  globalPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers);
    ~QtScriptShell_QMouseEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QMOUSEEVENT_H
