#include "qtscriptshell_QInputEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QInputEvent::QtScriptShell_QInputEvent(QEvent::Type  type, Qt::KeyboardModifiers  modifiers)
    : QInputEvent(type, modifiers) {}

QtScriptShell_QInputEvent::~QtScriptShell_QInputEvent() {}

