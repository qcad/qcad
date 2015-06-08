#ifndef QTSCRIPTSHELL_QTABLETEVENT_H
#define QTSCRIPTSHELL_QTABLETEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTabletEvent : public QTabletEvent
{
public:
    QtScriptShell_QTabletEvent(QEvent::Type  t, const QPointF&  pos, const QPointF&  globalPos, int  device, int  pointerType, qreal  pressure, int  xTilt, int  yTilt, qreal  tangentialPressure, qreal  rotation, int  z, Qt::KeyboardModifiers  keyState, qint64  uniqueID);
    ~QtScriptShell_QTabletEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTABLETEVENT_H
