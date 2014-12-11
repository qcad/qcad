#ifndef QTSCRIPTSHELL_QWHEELEVENT_H
#define QTSCRIPTSHELL_QWHEELEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QWheelEvent : public QWheelEvent
{
public:
    QtScriptShell_QWheelEvent(const QPointF&  pos, const QPointF&  globalPos, QPoint  pixelDelta, QPoint  angleDelta, int  qt4Delta, Qt::Orientation  qt4Orientation, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers);
    QtScriptShell_QWheelEvent(const QPointF&  pos, const QPointF&  globalPos, int  delta, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, Qt::Orientation  orient = Qt::Vertical);
    QtScriptShell_QWheelEvent(const QPointF&  pos, int  delta, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, Qt::Orientation  orient = Qt::Vertical);
    ~QtScriptShell_QWheelEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QWHEELEVENT_H
