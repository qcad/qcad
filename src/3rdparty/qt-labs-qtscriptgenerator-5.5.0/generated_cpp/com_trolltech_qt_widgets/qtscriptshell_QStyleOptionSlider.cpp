#include "qtscriptshell_QStyleOptionSlider.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionSlider::QtScriptShell_QStyleOptionSlider()
    : QStyleOptionSlider() {}

QtScriptShell_QStyleOptionSlider::QtScriptShell_QStyleOptionSlider(const QStyleOptionSlider&  other)
    : QStyleOptionSlider(other) {}

QtScriptShell_QStyleOptionSlider::QtScriptShell_QStyleOptionSlider(int  version)
    : QStyleOptionSlider(version) {}

QtScriptShell_QStyleOptionSlider::~QtScriptShell_QStyleOptionSlider() {}

