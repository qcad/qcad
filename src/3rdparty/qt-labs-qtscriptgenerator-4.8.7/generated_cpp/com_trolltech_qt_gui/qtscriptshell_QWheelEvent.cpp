#include "qtscriptshell_QWheelEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWheelEvent::QtScriptShell_QWheelEvent(const QPoint&  pos, const QPoint&  globalPos, int  delta, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, Qt::Orientation  orient)
    : QWheelEvent(pos, globalPos, delta, buttons, modifiers, orient) {}

QtScriptShell_QWheelEvent::QtScriptShell_QWheelEvent(const QPoint&  pos, int  delta, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, Qt::Orientation  orient)
    : QWheelEvent(pos, delta, buttons, modifiers, orient) {}

QtScriptShell_QWheelEvent::~QtScriptShell_QWheelEvent() {}

