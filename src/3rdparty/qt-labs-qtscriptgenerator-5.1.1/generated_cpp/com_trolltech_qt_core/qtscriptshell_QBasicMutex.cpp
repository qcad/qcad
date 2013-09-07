#include "qtscriptshell_QBasicMutex.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QBasicMutex::QtScriptShell_QBasicMutex()
    : QBasicMutex() {}

QtScriptShell_QBasicMutex::~QtScriptShell_QBasicMutex() {}

