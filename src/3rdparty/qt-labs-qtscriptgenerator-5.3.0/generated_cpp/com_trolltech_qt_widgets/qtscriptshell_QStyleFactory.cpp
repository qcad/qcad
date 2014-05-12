#include "qtscriptshell_QStyleFactory.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstringlist.h>
#include <qstyle.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleFactory::QtScriptShell_QStyleFactory()
    : QStyleFactory() {}

QtScriptShell_QStyleFactory::~QtScriptShell_QStyleFactory() {}

