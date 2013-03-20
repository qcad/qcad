#include "qtscriptshell_QAccessible2Interface.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QAccessible2Interface::QtScriptShell_QAccessible2Interface()
    : QAccessible2Interface() {}

QtScriptShell_QAccessible2Interface::~QtScriptShell_QAccessible2Interface() {}

