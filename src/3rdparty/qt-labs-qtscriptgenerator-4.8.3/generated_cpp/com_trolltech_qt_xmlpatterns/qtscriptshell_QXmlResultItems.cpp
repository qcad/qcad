#include "qtscriptshell_QXmlResultItems.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qabstractxmlnodemodel.h>
#include <qxmlresultitems.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlResultItems::QtScriptShell_QXmlResultItems()
    : QXmlResultItems() {}

QtScriptShell_QXmlResultItems::~QtScriptShell_QXmlResultItems() {}

