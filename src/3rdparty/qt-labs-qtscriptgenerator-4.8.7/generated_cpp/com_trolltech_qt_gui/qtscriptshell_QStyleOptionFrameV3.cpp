#include "qtscriptshell_QStyleOptionFrameV3.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionFrameV3::QtScriptShell_QStyleOptionFrameV3()
    : QStyleOptionFrameV3() {}

QtScriptShell_QStyleOptionFrameV3::QtScriptShell_QStyleOptionFrameV3(const QStyleOptionFrame&  other)
    : QStyleOptionFrameV3(other) {}

QtScriptShell_QStyleOptionFrameV3::QtScriptShell_QStyleOptionFrameV3(const QStyleOptionFrameV3&  other)
    : QStyleOptionFrameV3(other) {}

QtScriptShell_QStyleOptionFrameV3::QtScriptShell_QStyleOptionFrameV3(int  version)
    : QStyleOptionFrameV3(version) {}

QtScriptShell_QStyleOptionFrameV3::~QtScriptShell_QStyleOptionFrameV3() {}

