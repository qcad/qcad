#include "qtscriptshell_QWebPluginFactory_MimeType.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qwebpluginfactory.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWebPluginFactory_MimeType::QtScriptShell_QWebPluginFactory_MimeType()
    : QWebPluginFactory::MimeType() {}

QtScriptShell_QWebPluginFactory_MimeType::~QtScriptShell_QWebPluginFactory_MimeType() {}

