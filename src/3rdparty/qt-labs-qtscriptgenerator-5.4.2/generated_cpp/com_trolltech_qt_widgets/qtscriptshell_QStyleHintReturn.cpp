#include "qtscriptshell_QStyleHintReturn.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleHintReturn::QtScriptShell_QStyleHintReturn(int  version, int  type)
    : QStyleHintReturn(version, type) {}

QtScriptShell_QStyleHintReturn::~QtScriptShell_QStyleHintReturn() {}

