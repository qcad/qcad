#include "qtscriptshell_QStyleOptionTab.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionTab::QtScriptShell_QStyleOptionTab()
    : QStyleOptionTab() {}

QtScriptShell_QStyleOptionTab::QtScriptShell_QStyleOptionTab(const QStyleOptionTab&  other)
    : QStyleOptionTab(other) {}

QtScriptShell_QStyleOptionTab::QtScriptShell_QStyleOptionTab(int  version)
    : QStyleOptionTab(version) {}

QtScriptShell_QStyleOptionTab::~QtScriptShell_QStyleOptionTab() {}

