#include "qtscriptshell_QStyleOptionTitleBar.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionTitleBar::QtScriptShell_QStyleOptionTitleBar()
    : QStyleOptionTitleBar() {}

QtScriptShell_QStyleOptionTitleBar::QtScriptShell_QStyleOptionTitleBar(const QStyleOptionTitleBar&  other)
    : QStyleOptionTitleBar(other) {}

QtScriptShell_QStyleOptionTitleBar::QtScriptShell_QStyleOptionTitleBar(int  version)
    : QStyleOptionTitleBar(version) {}

QtScriptShell_QStyleOptionTitleBar::~QtScriptShell_QStyleOptionTitleBar() {}

