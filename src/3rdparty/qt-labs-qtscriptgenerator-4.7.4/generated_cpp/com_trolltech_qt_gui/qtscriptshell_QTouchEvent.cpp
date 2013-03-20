#include "qtscriptshell_QTouchEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qevent.h>
#include <qlist.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTouchEvent::QtScriptShell_QTouchEvent(QEvent::Type  eventType, QTouchEvent::DeviceType  deviceType, Qt::KeyboardModifiers  modifiers, Qt::TouchPointStates  touchPointStates, const QList<QTouchEvent::TouchPoint >&  touchPoints)
    : QTouchEvent(eventType, deviceType, modifiers, touchPointStates, touchPoints) {}

QtScriptShell_QTouchEvent::~QtScriptShell_QTouchEvent() {}

