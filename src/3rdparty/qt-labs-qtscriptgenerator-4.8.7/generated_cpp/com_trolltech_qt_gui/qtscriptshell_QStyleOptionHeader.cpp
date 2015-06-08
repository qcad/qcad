#include "qtscriptshell_QStyleOptionHeader.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionHeader::QtScriptShell_QStyleOptionHeader()
    : QStyleOptionHeader() {}

QtScriptShell_QStyleOptionHeader::QtScriptShell_QStyleOptionHeader(const QStyleOptionHeader&  other)
    : QStyleOptionHeader(other) {}

QtScriptShell_QStyleOptionHeader::QtScriptShell_QStyleOptionHeader(int  version)
    : QStyleOptionHeader(version) {}

QtScriptShell_QStyleOptionHeader::~QtScriptShell_QStyleOptionHeader() {}

