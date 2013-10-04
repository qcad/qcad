#include "qtscriptshell_QMouseEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qevent.h>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QMouseEvent::QtScriptShell_QMouseEvent(QEvent::Type  type, const QPoint&  pos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers)
    : QMouseEvent(type, pos, button, buttons, modifiers) {}

QtScriptShell_QMouseEvent::QtScriptShell_QMouseEvent(QEvent::Type  type, const QPoint&  pos, const QPoint&  globalPos, Qt::MouseButton  button, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers)
    : QMouseEvent(type, pos, globalPos, button, buttons, modifiers) {}

QtScriptShell_QMouseEvent::~QtScriptShell_QMouseEvent() {}

