#include "qtscriptshell_QResizeEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qsize.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QResizeEvent::QtScriptShell_QResizeEvent(const QSize&  size, const QSize&  oldSize)
    : QResizeEvent(size, oldSize) {}

QtScriptShell_QResizeEvent::~QtScriptShell_QResizeEvent() {}

