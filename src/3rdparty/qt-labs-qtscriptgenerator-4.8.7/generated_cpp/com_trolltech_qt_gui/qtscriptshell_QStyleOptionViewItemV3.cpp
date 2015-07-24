#include "qtscriptshell_QStyleOptionViewItemV3.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionViewItemV3::QtScriptShell_QStyleOptionViewItemV3()
    : QStyleOptionViewItemV3() {}

QtScriptShell_QStyleOptionViewItemV3::QtScriptShell_QStyleOptionViewItemV3(const QStyleOptionViewItem&  other)
    : QStyleOptionViewItemV3(other) {}

QtScriptShell_QStyleOptionViewItemV3::QtScriptShell_QStyleOptionViewItemV3(const QStyleOptionViewItemV3&  other)
    : QStyleOptionViewItemV3(other) {}

QtScriptShell_QStyleOptionViewItemV3::QtScriptShell_QStyleOptionViewItemV3(int  version)
    : QStyleOptionViewItemV3(version) {}

QtScriptShell_QStyleOptionViewItemV3::~QtScriptShell_QStyleOptionViewItemV3() {}

