#include "qtscriptshell_QDragMoveEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qmimedata.h>
#include <qobject.h>
#include <qpoint.h>
#include <qrect.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QDragMoveEvent::QtScriptShell_QDragMoveEvent(const QPoint&  pos, Qt::DropActions  actions, const QMimeData*  data, Qt::MouseButtons  buttons, Qt::KeyboardModifiers  modifiers, QEvent::Type  type)
    : QDragMoveEvent(pos, actions, data, buttons, modifiers, type) {}

QtScriptShell_QDragMoveEvent::~QtScriptShell_QDragMoveEvent() {}

