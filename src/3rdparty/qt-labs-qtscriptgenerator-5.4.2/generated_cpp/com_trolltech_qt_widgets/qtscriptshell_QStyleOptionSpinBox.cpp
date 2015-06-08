#include "qtscriptshell_QStyleOptionSpinBox.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionSpinBox::QtScriptShell_QStyleOptionSpinBox()
    : QStyleOptionSpinBox() {}

QtScriptShell_QStyleOptionSpinBox::QtScriptShell_QStyleOptionSpinBox(const QStyleOptionSpinBox&  other)
    : QStyleOptionSpinBox(other) {}

QtScriptShell_QStyleOptionSpinBox::QtScriptShell_QStyleOptionSpinBox(int  version)
    : QStyleOptionSpinBox(version) {}

QtScriptShell_QStyleOptionSpinBox::~QtScriptShell_QStyleOptionSpinBox() {}

