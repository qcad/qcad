#include "qtscriptshell_QStyleOption.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOption::QtScriptShell_QStyleOption(const QStyleOption&  other)
    : QStyleOption(other) {}

QtScriptShell_QStyleOption::QtScriptShell_QStyleOption(int  version, int  type)
    : QStyleOption(version, type) {}

QtScriptShell_QStyleOption::~QtScriptShell_QStyleOption() {}

