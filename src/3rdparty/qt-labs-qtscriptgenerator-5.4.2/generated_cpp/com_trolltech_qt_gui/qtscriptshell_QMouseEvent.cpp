#include "qtscriptshell_QMouseEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QMouseEvent::QtScriptShell_QMouseEvent(QEvent::Type  type, const QPointF&  localPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers)
    : QMouseEvent(type, localPos, button, buttons, modifiers) {}

QtScriptShell_QMouseEvent::QtScriptShell_QMouseEvent(QEvent::Type  type, const QPointF&  localPos, const QPointF&  screenPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers)
    : QMouseEvent(type, localPos, screenPos, button, buttons, modifiers) {}

QtScriptShell_QMouseEvent::QtScriptShell_QMouseEvent(QEvent::Type  type, const QPointF&  localPos, const QPointF&  windowPos, const QPointF&  screenPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers)
    : QMouseEvent(type, localPos, windowPos, screenPos, button, buttons, modifiers) {}

QtScriptShell_QMouseEvent::~QtScriptShell_QMouseEvent() {}

