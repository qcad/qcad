#include "qtscriptshell_QEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QEvent::QtScriptShell_QEvent(QEvent::Type  type)
    : QEvent(type) {}

QtScriptShell_QEvent::QtScriptShell_QEvent(const QEvent&  other)
    : QEvent(other) {}

QtScriptShell_QEvent::~QtScriptShell_QEvent() {}

