#include "qtscriptshell_QTextBlockUserData.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextBlockUserData::QtScriptShell_QTextBlockUserData()
    : QTextBlockUserData() {}

QtScriptShell_QTextBlockUserData::~QtScriptShell_QTextBlockUserData() {}

