#include "qtscriptshell_QStyleOptionGraphicsItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qtransform.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionGraphicsItem::QtScriptShell_QStyleOptionGraphicsItem()
    : QStyleOptionGraphicsItem() {}

QtScriptShell_QStyleOptionGraphicsItem::QtScriptShell_QStyleOptionGraphicsItem(const QStyleOptionGraphicsItem&  other)
    : QStyleOptionGraphicsItem(other) {}

QtScriptShell_QStyleOptionGraphicsItem::QtScriptShell_QStyleOptionGraphicsItem(int  version)
    : QStyleOptionGraphicsItem(version) {}

QtScriptShell_QStyleOptionGraphicsItem::~QtScriptShell_QStyleOptionGraphicsItem() {}

