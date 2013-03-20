#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTABBARBASEV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTABBARBASEV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionTabBarBaseV2 : public QStyleOptionTabBarBaseV2
{
public:
    QtScriptShell_QStyleOptionTabBarBaseV2();
    QtScriptShell_QStyleOptionTabBarBaseV2(const QStyleOptionTabBarBase&  other);
    QtScriptShell_QStyleOptionTabBarBaseV2(const QStyleOptionTabBarBaseV2&  other);
    QtScriptShell_QStyleOptionTabBarBaseV2(int  version);
    ~QtScriptShell_QStyleOptionTabBarBaseV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTABBARBASEV2_H
