#include "qtscriptshell_QFutureWatcher.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qfuture.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QFutureWatcher::QtScriptShell_QFutureWatcher()
    : QtScriptFutureWatcher() {}

QtScriptShell_QFutureWatcher::~QtScriptShell_QFutureWatcher() {}

