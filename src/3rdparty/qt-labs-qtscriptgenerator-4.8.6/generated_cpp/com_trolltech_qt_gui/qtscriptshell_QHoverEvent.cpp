#include "qtscriptshell_QHoverEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QHoverEvent::QtScriptShell_QHoverEvent(QEvent::Type  type, const QPoint&  pos, const QPoint&  oldPos)
    : QHoverEvent(type, pos, oldPos) {}

QtScriptShell_QHoverEvent::~QtScriptShell_QHoverEvent() {}

