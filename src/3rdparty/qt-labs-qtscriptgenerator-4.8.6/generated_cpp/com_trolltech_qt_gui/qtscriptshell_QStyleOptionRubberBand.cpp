#include "qtscriptshell_QStyleOptionRubberBand.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionRubberBand::QtScriptShell_QStyleOptionRubberBand()
    : QStyleOptionRubberBand() {}

QtScriptShell_QStyleOptionRubberBand::QtScriptShell_QStyleOptionRubberBand(const QStyleOptionRubberBand&  other)
    : QStyleOptionRubberBand(other) {}

QtScriptShell_QStyleOptionRubberBand::QtScriptShell_QStyleOptionRubberBand(int  version)
    : QStyleOptionRubberBand(version) {}

QtScriptShell_QStyleOptionRubberBand::~QtScriptShell_QStyleOptionRubberBand() {}

