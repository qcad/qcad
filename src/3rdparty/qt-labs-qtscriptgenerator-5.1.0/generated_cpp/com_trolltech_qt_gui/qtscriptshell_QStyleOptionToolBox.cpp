#include "qtscriptshell_QStyleOptionToolBox.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionToolBox::QtScriptShell_QStyleOptionToolBox()
    : QStyleOptionToolBox() {}

QtScriptShell_QStyleOptionToolBox::QtScriptShell_QStyleOptionToolBox(const QStyleOptionToolBox&  other)
    : QStyleOptionToolBox(other) {}

QtScriptShell_QStyleOptionToolBox::QtScriptShell_QStyleOptionToolBox(int  version)
    : QStyleOptionToolBox(version) {}

QtScriptShell_QStyleOptionToolBox::~QtScriptShell_QStyleOptionToolBox() {}

