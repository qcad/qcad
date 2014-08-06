#include "qtscriptshell_QDropEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpoint.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QDropEvent::QtScriptShell_QDropEvent(const QPointF&  pos, Qt::DropActions  actions, const QMimeData*  data, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, QEvent::Type  type)
    : QDropEvent(pos, actions, data, buttons, modifiers, type) {}

QtScriptShell_QDropEvent::~QtScriptShell_QDropEvent() {}

