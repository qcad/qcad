#include "qtscriptshell_QWebPage_ExtensionReturn.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWebPage_ExtensionReturn::QtScriptShell_QWebPage_ExtensionReturn()
    : QWebPage::ExtensionReturn() {}

QtScriptShell_QWebPage_ExtensionReturn::~QtScriptShell_QWebPage_ExtensionReturn() {}

