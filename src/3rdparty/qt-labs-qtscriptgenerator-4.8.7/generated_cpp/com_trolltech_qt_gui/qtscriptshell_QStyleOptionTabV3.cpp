#include "qtscriptshell_QStyleOptionTabV3.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionTabV3::QtScriptShell_QStyleOptionTabV3()
    : QStyleOptionTabV3() {}

QtScriptShell_QStyleOptionTabV3::QtScriptShell_QStyleOptionTabV3(const QStyleOptionTab&  other)
    : QStyleOptionTabV3(other) {}

QtScriptShell_QStyleOptionTabV3::QtScriptShell_QStyleOptionTabV3(const QStyleOptionTabV2&  other)
    : QStyleOptionTabV3(other) {}

QtScriptShell_QStyleOptionTabV3::QtScriptShell_QStyleOptionTabV3(const QStyleOptionTabV3&  other)
    : QStyleOptionTabV3(other) {}

QtScriptShell_QStyleOptionTabV3::QtScriptShell_QStyleOptionTabV3(int  version)
    : QStyleOptionTabV3(version) {}

QtScriptShell_QStyleOptionTabV3::~QtScriptShell_QStyleOptionTabV3() {}

