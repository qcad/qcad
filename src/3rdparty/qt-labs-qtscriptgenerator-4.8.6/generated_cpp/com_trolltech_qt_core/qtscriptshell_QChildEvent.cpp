#include "qtscriptshell_QChildEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qobject.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QChildEvent::QtScriptShell_QChildEvent(QEvent::Type  type, QObject*  child)
    : QChildEvent(type, child) {}

QtScriptShell_QChildEvent::~QtScriptShell_QChildEvent() {}

