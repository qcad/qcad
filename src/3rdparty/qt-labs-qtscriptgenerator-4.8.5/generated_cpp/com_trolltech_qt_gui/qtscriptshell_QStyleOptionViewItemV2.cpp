#include "qtscriptshell_QStyleOptionViewItemV2.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionViewItemV2::QtScriptShell_QStyleOptionViewItemV2()
    : QStyleOptionViewItemV2() {}

QtScriptShell_QStyleOptionViewItemV2::QtScriptShell_QStyleOptionViewItemV2(const QStyleOptionViewItem&  other)
    : QStyleOptionViewItemV2(other) {}

QtScriptShell_QStyleOptionViewItemV2::QtScriptShell_QStyleOptionViewItemV2(const QStyleOptionViewItemV2&  other)
    : QStyleOptionViewItemV2(other) {}

QtScriptShell_QStyleOptionViewItemV2::QtScriptShell_QStyleOptionViewItemV2(int  version)
    : QStyleOptionViewItemV2(version) {}

QtScriptShell_QStyleOptionViewItemV2::~QtScriptShell_QStyleOptionViewItemV2() {}

