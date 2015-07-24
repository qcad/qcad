#include "qtscriptshell_QIPv6Address.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QIPv6Address::QtScriptShell_QIPv6Address()
    : QIPv6Address() {}

QtScriptShell_QIPv6Address::~QtScriptShell_QIPv6Address() {}

