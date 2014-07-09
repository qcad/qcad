#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTITLEBAR_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTITLEBAR_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionTitleBar : public QStyleOptionTitleBar
{
public:
    QtScriptShell_QStyleOptionTitleBar();
    QtScriptShell_QStyleOptionTitleBar(const QStyleOptionTitleBar&  other);
    QtScriptShell_QStyleOptionTitleBar(int  version);
    ~QtScriptShell_QStyleOptionTitleBar();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTITLEBAR_H
