#ifndef QTSCRIPTSHELL_QTABLETEVENT_H
#define QTSCRIPTSHELL_QTABLETEVENT_H

#include <qevent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTabletEvent : public QTabletEvent
{
public:
    QtScriptShell_QTabletEvent(QEvent::Type  t, const QPoint&  pos, const QPoint&  globalPos, const QPointF&  hiResGlobalPos, int  device, int  pointerType, qreal  pressure, int  xTilt, int  yTilt, qreal  tangentialPressure, qreal  rotation, int  z, Qt::KeyboardModifiers  keyState, qint64  uniqueID);
    ~QtScriptShell_QTabletEvent();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTABLETEVENT_H
