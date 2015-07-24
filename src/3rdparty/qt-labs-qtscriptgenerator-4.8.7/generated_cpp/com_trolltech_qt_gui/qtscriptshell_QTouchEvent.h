#ifndef QTSCRIPTSHELL_QTOUCHEVENT_H
#define QTSCRIPTSHELL_QTOUCHEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTouchEvent : public QTouchEvent
{
public:
    QtScriptShell_QTouchEvent(QEvent::Type  eventType, QTouchEvent::DeviceType  deviceType = QTouchEvent::TouchScreen, Qt::KeyboardModifiers  modifiers = Qt::NoModifier, Qt::TouchPointStates  touchPointStates = 0, const QList<QTouchEvent::TouchPoint >&  touchPoints = QList<QTouchEvent::TouchPoint>());
    ~QtScriptShell_QTouchEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTOUCHEVENT_H
