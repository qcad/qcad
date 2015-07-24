#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTOOLBUTTON_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTOOLBUTTON_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionToolButton : public QStyleOptionToolButton
{
public:
    QtScriptShell_QStyleOptionToolButton();
    QtScriptShell_QStyleOptionToolButton(const QStyleOptionToolButton&  other);
    QtScriptShell_QStyleOptionToolButton(int  version);
    ~QtScriptShell_QStyleOptionToolButton();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTOOLBUTTON_H
