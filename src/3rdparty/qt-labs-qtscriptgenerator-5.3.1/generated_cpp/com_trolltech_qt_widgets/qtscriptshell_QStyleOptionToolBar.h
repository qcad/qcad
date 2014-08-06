#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTOOLBAR_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTOOLBAR_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionToolBar : public QStyleOptionToolBar
{
public:
    QtScriptShell_QStyleOptionToolBar();
    QtScriptShell_QStyleOptionToolBar(const QStyleOptionToolBar&  other);
    QtScriptShell_QStyleOptionToolBar(int  version);
    ~QtScriptShell_QStyleOptionToolBar();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTOOLBAR_H
