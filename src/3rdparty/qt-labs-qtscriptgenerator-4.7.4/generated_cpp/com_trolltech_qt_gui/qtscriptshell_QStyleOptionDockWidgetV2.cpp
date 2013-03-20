#include "qtscriptshell_QStyleOptionDockWidgetV2.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionDockWidgetV2::QtScriptShell_QStyleOptionDockWidgetV2()
    : QStyleOptionDockWidgetV2() {}

QtScriptShell_QStyleOptionDockWidgetV2::QtScriptShell_QStyleOptionDockWidgetV2(const QStyleOptionDockWidget&  other)
    : QStyleOptionDockWidgetV2(other) {}

QtScriptShell_QStyleOptionDockWidgetV2::QtScriptShell_QStyleOptionDockWidgetV2(const QStyleOptionDockWidgetV2&  other)
    : QStyleOptionDockWidgetV2(other) {}

QtScriptShell_QStyleOptionDockWidgetV2::QtScriptShell_QStyleOptionDockWidgetV2(int  version)
    : QStyleOptionDockWidgetV2(version) {}

QtScriptShell_QStyleOptionDockWidgetV2::~QtScriptShell_QStyleOptionDockWidgetV2() {}

