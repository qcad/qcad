#include "qtscriptshell_QHoverEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QHoverEvent::QtScriptShell_QHoverEvent(QEvent::Type  type, const QPointF&  pos, const QPointF&  oldPos, Qt::KeyboardModifiers  modifiers)
    : QHoverEvent(type, pos, oldPos, modifiers) {}

QtScriptShell_QHoverEvent::~QtScriptShell_QHoverEvent() {}

