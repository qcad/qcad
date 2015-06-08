#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTABBARBASE_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTABBARBASE_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionTabBarBase : public QStyleOptionTabBarBase
{
public:
    QtScriptShell_QStyleOptionTabBarBase();
    QtScriptShell_QStyleOptionTabBarBase(const QStyleOptionTabBarBase&  other);
    QtScriptShell_QStyleOptionTabBarBase(int  version);
    ~QtScriptShell_QStyleOptionTabBarBase();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTABBARBASE_H
