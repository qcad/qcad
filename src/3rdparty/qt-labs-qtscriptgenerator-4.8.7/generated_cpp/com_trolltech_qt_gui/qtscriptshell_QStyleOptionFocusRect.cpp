#include "qtscriptshell_QStyleOptionFocusRect.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionFocusRect::QtScriptShell_QStyleOptionFocusRect()
    : QStyleOptionFocusRect() {}

QtScriptShell_QStyleOptionFocusRect::QtScriptShell_QStyleOptionFocusRect(const QStyleOptionFocusRect&  other)
    : QStyleOptionFocusRect(other) {}

QtScriptShell_QStyleOptionFocusRect::QtScriptShell_QStyleOptionFocusRect(int  version)
    : QStyleOptionFocusRect(version) {}

QtScriptShell_QStyleOptionFocusRect::~QtScriptShell_QStyleOptionFocusRect() {}

