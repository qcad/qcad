#include "qtscriptshell_QStyleOptionProgressBar.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionProgressBar::QtScriptShell_QStyleOptionProgressBar()
    : QStyleOptionProgressBar() {}

QtScriptShell_QStyleOptionProgressBar::QtScriptShell_QStyleOptionProgressBar(const QStyleOptionProgressBar&  other)
    : QStyleOptionProgressBar(other) {}

QtScriptShell_QStyleOptionProgressBar::QtScriptShell_QStyleOptionProgressBar(int  version)
    : QStyleOptionProgressBar(version) {}

QtScriptShell_QStyleOptionProgressBar::~QtScriptShell_QStyleOptionProgressBar() {}

