#include "qtscriptshell_QStyleOptionTabV2.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionTabV2::QtScriptShell_QStyleOptionTabV2()
    : QStyleOptionTabV2() {}

QtScriptShell_QStyleOptionTabV2::QtScriptShell_QStyleOptionTabV2(const QStyleOptionTab&  other)
    : QStyleOptionTabV2(other) {}

QtScriptShell_QStyleOptionTabV2::QtScriptShell_QStyleOptionTabV2(const QStyleOptionTabV2&  other)
    : QStyleOptionTabV2(other) {}

QtScriptShell_QStyleOptionTabV2::QtScriptShell_QStyleOptionTabV2(int  version)
    : QStyleOptionTabV2(version) {}

QtScriptShell_QStyleOptionTabV2::~QtScriptShell_QStyleOptionTabV2() {}

