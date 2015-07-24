#include "qtscriptshell_QContextMenuEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QContextMenuEvent::QtScriptShell_QContextMenuEvent(QContextMenuEvent::Reason  reason, const QPoint&  pos)
    : QContextMenuEvent(reason, pos) {}

QtScriptShell_QContextMenuEvent::QtScriptShell_QContextMenuEvent(QContextMenuEvent::Reason  reason, const QPoint&  pos, const QPoint&  globalPos)
    : QContextMenuEvent(reason, pos, globalPos) {}

QtScriptShell_QContextMenuEvent::QtScriptShell_QContextMenuEvent(QContextMenuEvent::Reason  reason, const QPoint&  pos, const QPoint&  globalPos, Qt::KeyboardModifiers  modifiers)
    : QContextMenuEvent(reason, pos, globalPos, modifiers) {}

QtScriptShell_QContextMenuEvent::~QtScriptShell_QContextMenuEvent() {}

