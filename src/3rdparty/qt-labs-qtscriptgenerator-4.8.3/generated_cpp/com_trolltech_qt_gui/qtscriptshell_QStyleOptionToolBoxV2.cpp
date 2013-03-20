#include "qtscriptshell_QStyleOptionToolBoxV2.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionToolBoxV2::QtScriptShell_QStyleOptionToolBoxV2()
    : QStyleOptionToolBoxV2() {}

QtScriptShell_QStyleOptionToolBoxV2::QtScriptShell_QStyleOptionToolBoxV2(const QStyleOptionToolBox&  other)
    : QStyleOptionToolBoxV2(other) {}

QtScriptShell_QStyleOptionToolBoxV2::QtScriptShell_QStyleOptionToolBoxV2(const QStyleOptionToolBoxV2&  other)
    : QStyleOptionToolBoxV2(other) {}

QtScriptShell_QStyleOptionToolBoxV2::QtScriptShell_QStyleOptionToolBoxV2(int  version)
    : QStyleOptionToolBoxV2(version) {}

QtScriptShell_QStyleOptionToolBoxV2::~QtScriptShell_QStyleOptionToolBoxV2() {}

