#include "qtscriptshell_QShortcutEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qkeysequence.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QShortcutEvent::QtScriptShell_QShortcutEvent(const QKeySequence&  key, int  id, bool  ambiguous)
    : QShortcutEvent(key, id, ambiguous) {}

QtScriptShell_QShortcutEvent::~QtScriptShell_QShortcutEvent() {}

