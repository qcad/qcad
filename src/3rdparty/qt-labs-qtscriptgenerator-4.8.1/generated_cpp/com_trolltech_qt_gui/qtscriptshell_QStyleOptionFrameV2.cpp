#include "qtscriptshell_QStyleOptionFrameV2.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionFrameV2::QtScriptShell_QStyleOptionFrameV2()
    : QStyleOptionFrameV2() {}

QtScriptShell_QStyleOptionFrameV2::QtScriptShell_QStyleOptionFrameV2(const QStyleOptionFrame&  other)
    : QStyleOptionFrameV2(other) {}

QtScriptShell_QStyleOptionFrameV2::QtScriptShell_QStyleOptionFrameV2(const QStyleOptionFrameV2&  other)
    : QStyleOptionFrameV2(other) {}

QtScriptShell_QStyleOptionFrameV2::QtScriptShell_QStyleOptionFrameV2(int  version)
    : QStyleOptionFrameV2(version) {}

QtScriptShell_QStyleOptionFrameV2::~QtScriptShell_QStyleOptionFrameV2() {}

