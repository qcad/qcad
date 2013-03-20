#include "qtscriptshell_QStyleOptionButton.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionButton::QtScriptShell_QStyleOptionButton()
    : QStyleOptionButton() {}

QtScriptShell_QStyleOptionButton::QtScriptShell_QStyleOptionButton(const QStyleOptionButton&  other)
    : QStyleOptionButton(other) {}

QtScriptShell_QStyleOptionButton::QtScriptShell_QStyleOptionButton(int  version)
    : QStyleOptionButton(version) {}

QtScriptShell_QStyleOptionButton::~QtScriptShell_QStyleOptionButton() {}

