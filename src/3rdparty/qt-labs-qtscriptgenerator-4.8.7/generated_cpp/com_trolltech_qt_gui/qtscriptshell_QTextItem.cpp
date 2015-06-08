#include "qtscriptshell_QTextItem.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qfont.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTextItem::QtScriptShell_QTextItem()
    : QTextItem() {}

QtScriptShell_QTextItem::~QtScriptShell_QTextItem() {}

