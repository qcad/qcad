#include "qtscriptshell_QStyleOptionComplex.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionComplex::QtScriptShell_QStyleOptionComplex(const QStyleOptionComplex&  other)
    : QStyleOptionComplex(other) {}

QtScriptShell_QStyleOptionComplex::QtScriptShell_QStyleOptionComplex(int  version, int  type)
    : QStyleOptionComplex(version, type) {}

QtScriptShell_QStyleOptionComplex::~QtScriptShell_QStyleOptionComplex() {}

