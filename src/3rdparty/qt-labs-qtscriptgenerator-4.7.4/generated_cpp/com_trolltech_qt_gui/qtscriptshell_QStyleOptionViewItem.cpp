#include "qtscriptshell_QStyleOptionViewItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionViewItem::QtScriptShell_QStyleOptionViewItem()
    : QStyleOptionViewItem() {}

QtScriptShell_QStyleOptionViewItem::QtScriptShell_QStyleOptionViewItem(const QStyleOptionViewItem&  other)
    : QStyleOptionViewItem(other) {}

QtScriptShell_QStyleOptionViewItem::QtScriptShell_QStyleOptionViewItem(int  version)
    : QStyleOptionViewItem(version) {}

QtScriptShell_QStyleOptionViewItem::~QtScriptShell_QStyleOptionViewItem() {}

