#include "qtscriptshell_QWebPluginFactory_ExtensionReturn.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWebPluginFactory_ExtensionReturn::QtScriptShell_QWebPluginFactory_ExtensionReturn()
    : QWebPluginFactory::ExtensionReturn() {}

QtScriptShell_QWebPluginFactory_ExtensionReturn::~QtScriptShell_QWebPluginFactory_ExtensionReturn() {}

