#include "qtscriptshell_QStyleOptionToolButton.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionToolButton::QtScriptShell_QStyleOptionToolButton()
    : QStyleOptionToolButton() {}

QtScriptShell_QStyleOptionToolButton::QtScriptShell_QStyleOptionToolButton(const QStyleOptionToolButton&  other)
    : QStyleOptionToolButton(other) {}

QtScriptShell_QStyleOptionToolButton::QtScriptShell_QStyleOptionToolButton(int  version)
    : QStyleOptionToolButton(version) {}

QtScriptShell_QStyleOptionToolButton::~QtScriptShell_QStyleOptionToolButton() {}

