#include "qtscriptshell_QDragResponseEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QDragResponseEvent::QtScriptShell_QDragResponseEvent(bool  accepted)
    : QDragResponseEvent(accepted) {}

QtScriptShell_QDragResponseEvent::~QtScriptShell_QDragResponseEvent() {}

