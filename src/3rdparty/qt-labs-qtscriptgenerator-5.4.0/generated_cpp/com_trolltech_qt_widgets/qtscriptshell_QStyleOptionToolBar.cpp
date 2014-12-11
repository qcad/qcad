#include "qtscriptshell_QStyleOptionToolBar.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionToolBar::QtScriptShell_QStyleOptionToolBar()
    : QStyleOptionToolBar() {}

QtScriptShell_QStyleOptionToolBar::QtScriptShell_QStyleOptionToolBar(const QStyleOptionToolBar&  other)
    : QStyleOptionToolBar(other) {}

QtScriptShell_QStyleOptionToolBar::QtScriptShell_QStyleOptionToolBar(int  version)
    : QStyleOptionToolBar(version) {}

QtScriptShell_QStyleOptionToolBar::~QtScriptShell_QStyleOptionToolBar() {}

