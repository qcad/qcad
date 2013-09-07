#include "qtscriptshell_QWebPluginFactory_ExtensionOption.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWebPluginFactory_ExtensionOption::QtScriptShell_QWebPluginFactory_ExtensionOption()
    : QWebPluginFactory::ExtensionOption() {}

QtScriptShell_QWebPluginFactory_ExtensionOption::~QtScriptShell_QWebPluginFactory_ExtensionOption() {}

