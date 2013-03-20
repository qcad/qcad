#include "qtscriptshell_QStyleOptionGroupBox.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionGroupBox::QtScriptShell_QStyleOptionGroupBox()
    : QStyleOptionGroupBox() {}

QtScriptShell_QStyleOptionGroupBox::QtScriptShell_QStyleOptionGroupBox(const QStyleOptionGroupBox&  other)
    : QStyleOptionGroupBox(other) {}

QtScriptShell_QStyleOptionGroupBox::QtScriptShell_QStyleOptionGroupBox(int  version)
    : QStyleOptionGroupBox(version) {}

QtScriptShell_QStyleOptionGroupBox::~QtScriptShell_QStyleOptionGroupBox() {}

