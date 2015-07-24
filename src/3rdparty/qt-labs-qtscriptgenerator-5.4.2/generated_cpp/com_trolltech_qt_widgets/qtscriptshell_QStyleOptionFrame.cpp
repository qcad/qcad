#include "qtscriptshell_QStyleOptionFrame.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionFrame::QtScriptShell_QStyleOptionFrame()
    : QStyleOptionFrame() {}

QtScriptShell_QStyleOptionFrame::QtScriptShell_QStyleOptionFrame(const QStyleOptionFrame&  other)
    : QStyleOptionFrame(other) {}

QtScriptShell_QStyleOptionFrame::QtScriptShell_QStyleOptionFrame(int  version)
    : QStyleOptionFrame(version) {}

QtScriptShell_QStyleOptionFrame::~QtScriptShell_QStyleOptionFrame() {}

