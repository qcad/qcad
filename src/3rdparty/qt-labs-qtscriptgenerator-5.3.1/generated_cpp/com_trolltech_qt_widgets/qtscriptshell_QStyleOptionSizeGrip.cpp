#include "qtscriptshell_QStyleOptionSizeGrip.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionSizeGrip::QtScriptShell_QStyleOptionSizeGrip()
    : QStyleOptionSizeGrip() {}

QtScriptShell_QStyleOptionSizeGrip::QtScriptShell_QStyleOptionSizeGrip(const QStyleOptionSizeGrip&  other)
    : QStyleOptionSizeGrip(other) {}

QtScriptShell_QStyleOptionSizeGrip::QtScriptShell_QStyleOptionSizeGrip(int  version)
    : QStyleOptionSizeGrip(version) {}

QtScriptShell_QStyleOptionSizeGrip::~QtScriptShell_QStyleOptionSizeGrip() {}

