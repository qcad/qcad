#include "qtscriptshell_QTabletEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTabletEvent::QtScriptShell_QTabletEvent(QEvent::Type  t, const QPoint&  pos, const QPoint&  globalPos, const QPointF&  hiResGlobalPos, int  device, int  pointerType, qreal  pressure, int  xTilt, int  yTilt, qreal  tangentialPressure, qreal  rotation, int  z, Qt::KeyboardModifiers  keyState, qint64  uniqueID)
    : QTabletEvent(t, pos, globalPos, hiResGlobalPos, device, pointerType, pressure, xTilt, yTilt, tangentialPressure, rotation, z, keyState, uniqueID) {}

QtScriptShell_QTabletEvent::~QtScriptShell_QTabletEvent() {}

