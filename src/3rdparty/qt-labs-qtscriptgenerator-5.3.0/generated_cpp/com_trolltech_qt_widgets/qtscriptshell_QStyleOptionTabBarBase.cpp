#include "qtscriptshell_QStyleOptionTabBarBase.h"

#include <QtScript/QScriptEngine>
#include <QVariant>
#include <qstyleoption.h>
#include <qwidget.h>

#define QTSCRIPT_IS_GENERATED_FUNCTION(fun) ((fun.data().toUInt32() & 0xFFFF0000) == 0xBABE0000)


QtScriptShell_QStyleOptionTabBarBase::QtScriptShell_QStyleOptionTabBarBase()
    : QStyleOptionTabBarBase() {}

QtScriptShell_QStyleOptionTabBarBase::QtScriptShell_QStyleOptionTabBarBase(const QStyleOptionTabBarBase&  other)
    : QStyleOptionTabBarBase(other) {}

QtScriptShell_QStyleOptionTabBarBase::QtScriptShell_QStyleOptionTabBarBase(int  version)
    : QStyleOptionTabBarBase(version) {}

QtScriptShell_QStyleOptionTabBarBase::~QtScriptShell_QStyleOptionTabBarBase() {}

