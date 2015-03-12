#include "qtscriptshell_QStyleOptionTabWidgetFrame.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionTabWidgetFrame::QtScriptShell_QStyleOptionTabWidgetFrame()
    : QStyleOptionTabWidgetFrame() {}

QtScriptShell_QStyleOptionTabWidgetFrame::QtScriptShell_QStyleOptionTabWidgetFrame(const QStyleOptionTabWidgetFrame&  other)
    : QStyleOptionTabWidgetFrame(other) {}

QtScriptShell_QStyleOptionTabWidgetFrame::QtScriptShell_QStyleOptionTabWidgetFrame(int  version)
    : QStyleOptionTabWidgetFrame(version) {}

QtScriptShell_QStyleOptionTabWidgetFrame::~QtScriptShell_QStyleOptionTabWidgetFrame() {}

