#include "qtscriptshell_QFuture.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QFuture::QtScriptShell_QFuture()
    : QtScriptFuture() {}

QtScriptShell_QFuture::~QtScriptShell_QFuture() {}

