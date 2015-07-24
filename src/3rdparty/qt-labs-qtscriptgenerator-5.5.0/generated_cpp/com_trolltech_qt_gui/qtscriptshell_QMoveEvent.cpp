#include "qtscriptshell_QMoveEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QMoveEvent::QtScriptShell_QMoveEvent(const QPoint&  pos, const QPoint&  oldPos)
    : QMoveEvent(pos, oldPos) {}

QtScriptShell_QMoveEvent::~QtScriptShell_QMoveEvent() {}

