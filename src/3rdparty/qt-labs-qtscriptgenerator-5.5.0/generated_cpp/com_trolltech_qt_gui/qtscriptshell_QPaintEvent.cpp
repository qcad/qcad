#include "qtscriptshell_QPaintEvent.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qcoreevent.h>
#include <qrect.h>
#include <qregion.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QPaintEvent::QtScriptShell_QPaintEvent(const QRect&  paintRect)
    : QPaintEvent(paintRect) {}

QtScriptShell_QPaintEvent::QtScriptShell_QPaintEvent(const QRegion&  paintRegion)
    : QPaintEvent(paintRegion) {}

QtScriptShell_QPaintEvent::~QtScriptShell_QPaintEvent() {}

