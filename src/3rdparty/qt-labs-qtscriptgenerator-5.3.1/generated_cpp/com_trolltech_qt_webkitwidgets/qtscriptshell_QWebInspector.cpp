#include "qtscriptshell_QWebInspector.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qwebpage.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QWebInspector::QtScriptShell_QWebInspector(QWidget*  parent)
    : QWebInspector(parent) {}

QtScriptShell_QWebInspector::~QtScriptShell_QWebInspector() {}

