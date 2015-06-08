#include "qtscriptshell_QStyleOptionMenuItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionMenuItem::QtScriptShell_QStyleOptionMenuItem()
    : QStyleOptionMenuItem() {}

QtScriptShell_QStyleOptionMenuItem::QtScriptShell_QStyleOptionMenuItem(const QStyleOptionMenuItem&  other)
    : QStyleOptionMenuItem(other) {}

QtScriptShell_QStyleOptionMenuItem::QtScriptShell_QStyleOptionMenuItem(int  version)
    : QStyleOptionMenuItem(version) {}

QtScriptShell_QStyleOptionMenuItem::~QtScriptShell_QStyleOptionMenuItem() {}

