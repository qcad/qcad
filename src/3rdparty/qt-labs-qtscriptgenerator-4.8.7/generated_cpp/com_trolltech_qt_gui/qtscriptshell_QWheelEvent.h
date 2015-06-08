#ifndef QTSCRIPTSHELL_QWHEELEVENT_H
#define QTSCRIPTSHELL_QWHEELEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QWheelEvent : public QWheelEvent
{
public:
    QtScriptShell_QWheelEvent(const QPoint&  pos, const QPoint&  globalPos, int  delta, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, Qt::Orientation  orient = Qt::Vertical);
    QtScriptShell_QWheelEvent(const QPoint&  pos, int  delta, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, Qt::Orientation  orient = Qt::Vertical);
    ~QtScriptShell_QWheelEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWHEELEVENT_H
