#include "qtscriptshell_QXmlStreamAttributes.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qlist.h>
#include <qvector.h>
#include <qxmlstream.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QXmlStreamAttributes::QtScriptShell_QXmlStreamAttributes()
    : QXmlStreamAttributes() {}

QtScriptShell_QXmlStreamAttributes::~QtScriptShell_QXmlStreamAttributes() {}

