#include "qtscriptshell_QDesktopServices.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qobject.h>
#include <qurl.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QDesktopServices::QtScriptShell_QDesktopServices()
    : QDesktopServices() {}

QtScriptShell_QDesktopServices::~QtScriptShell_QDesktopServices() {}

