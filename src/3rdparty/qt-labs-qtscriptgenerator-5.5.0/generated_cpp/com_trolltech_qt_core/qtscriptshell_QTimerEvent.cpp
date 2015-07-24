#include "qtscriptshell_QTimerEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QTimerEvent::QtScriptShell_QTimerEvent(int  timerId)
    : QTimerEvent(timerId) {}

QtScriptShell_QTimerEvent::~QtScriptShell_QTimerEvent() {}

