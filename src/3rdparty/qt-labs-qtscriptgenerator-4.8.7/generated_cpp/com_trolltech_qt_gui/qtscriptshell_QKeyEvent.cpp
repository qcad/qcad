#include "qtscriptshell_QKeyEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qevent.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QKeyEvent::QtScriptShell_QKeyEvent(QEvent::Type  type, int  key, Qt::KeyboardModifiers  modifiers, const QString&  text, bool  autorep, ushort  count)
    : QKeyEvent(type, key, modifiers, text, autorep, count) {}

QtScriptShell_QKeyEvent::~QtScriptShell_QKeyEvent() {}

