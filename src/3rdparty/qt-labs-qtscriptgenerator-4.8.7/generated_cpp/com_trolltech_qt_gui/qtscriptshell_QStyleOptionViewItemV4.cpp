#include "qtscriptshell_QStyleOptionViewItemV4.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionViewItemV4::QtScriptShell_QStyleOptionViewItemV4()
    : QStyleOptionViewItemV4() {}

QtScriptShell_QStyleOptionViewItemV4::QtScriptShell_QStyleOptionViewItemV4(const QStyleOptionViewItem&  other)
    : QStyleOptionViewItemV4(other) {}

QtScriptShell_QStyleOptionViewItemV4::QtScriptShell_QStyleOptionViewItemV4(const QStyleOptionViewItemV4&  other)
    : QStyleOptionViewItemV4(other) {}

QtScriptShell_QStyleOptionViewItemV4::QtScriptShell_QStyleOptionViewItemV4(int  version)
    : QStyleOptionViewItemV4(version) {}

QtScriptShell_QStyleOptionViewItemV4::~QtScriptShell_QStyleOptionViewItemV4() {}

