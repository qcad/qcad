#include "qtscriptshell_QStyleOptionComboBox.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionComboBox::QtScriptShell_QStyleOptionComboBox()
    : QStyleOptionComboBox() {}

QtScriptShell_QStyleOptionComboBox::QtScriptShell_QStyleOptionComboBox(const QStyleOptionComboBox&  other)
    : QStyleOptionComboBox(other) {}

QtScriptShell_QStyleOptionComboBox::QtScriptShell_QStyleOptionComboBox(int  version)
    : QStyleOptionComboBox(version) {}

QtScriptShell_QStyleOptionComboBox::~QtScriptShell_QStyleOptionComboBox() {}

