#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTAB_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTAB_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionTab : public QStyleOptionTab
{
public:
    QtScriptShell_QStyleOptionTab();
    QtScriptShell_QStyleOptionTab(const QStyleOptionTab&  other);
    QtScriptShell_QStyleOptionTab(int  version);
    ~QtScriptShell_QStyleOptionTab();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTAB_H
