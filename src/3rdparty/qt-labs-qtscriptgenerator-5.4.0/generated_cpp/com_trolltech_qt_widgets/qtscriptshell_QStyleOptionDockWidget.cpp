#include "qtscriptshell_QStyleOptionDockWidget.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionDockWidget::QtScriptShell_QStyleOptionDockWidget()
    : QStyleOptionDockWidget() {}

QtScriptShell_QStyleOptionDockWidget::QtScriptShell_QStyleOptionDockWidget(const QStyleOptionDockWidget&  other)
    : QStyleOptionDockWidget(other) {}

QtScriptShell_QStyleOptionDockWidget::QtScriptShell_QStyleOptionDockWidget(int  version)
    : QStyleOptionDockWidget(version) {}

QtScriptShell_QStyleOptionDockWidget::~QtScriptShell_QStyleOptionDockWidget() {}

