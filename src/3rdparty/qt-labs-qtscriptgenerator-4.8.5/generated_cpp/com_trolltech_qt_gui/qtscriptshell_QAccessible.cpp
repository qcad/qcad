#include "qtscriptshell_QAccessible.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qaccessible.h>
#include <qobject.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QAccessible::QtScriptShell_QAccessible()
    : QAccessible() {}

QtScriptShell_QAccessible::~QtScriptShell_QAccessible() {}

