#include "qtscriptshell_QInputContextFactory.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qinputcontext.h>
#include <qobject.h>
#include <qstringlist.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QInputContextFactory::QtScriptShell_QInputContextFactory()
    : QInputContextFactory() {}

QtScriptShell_QInputContextFactory::~QtScriptShell_QInputContextFactory() {}

