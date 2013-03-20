#include "qtscriptshell_QStyleOptionProgressBarV2.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionProgressBarV2::QtScriptShell_QStyleOptionProgressBarV2()
    : QStyleOptionProgressBarV2() {}

QtScriptShell_QStyleOptionProgressBarV2::QtScriptShell_QStyleOptionProgressBarV2(const QStyleOptionProgressBar&  other)
    : QStyleOptionProgressBarV2(other) {}

QtScriptShell_QStyleOptionProgressBarV2::QtScriptShell_QStyleOptionProgressBarV2(const QStyleOptionProgressBarV2&  other)
    : QStyleOptionProgressBarV2(other) {}

QtScriptShell_QStyleOptionProgressBarV2::QtScriptShell_QStyleOptionProgressBarV2(int  version)
    : QStyleOptionProgressBarV2(version) {}

QtScriptShell_QStyleOptionProgressBarV2::~QtScriptShell_QStyleOptionProgressBarV2() {}

