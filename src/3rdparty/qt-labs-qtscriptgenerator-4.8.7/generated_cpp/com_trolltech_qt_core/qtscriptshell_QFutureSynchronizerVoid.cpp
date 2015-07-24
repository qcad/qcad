#include "qtscriptshell_QFutureSynchronizerVoid.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QFutureSynchronizerVoid::QtScriptShell_QFutureSynchronizerVoid()
    : QtScriptVoidFutureSynchronizer() {}

QtScriptShell_QFutureSynchronizerVoid::~QtScriptShell_QFutureSynchronizerVoid() {}

