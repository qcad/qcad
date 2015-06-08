#ifndef QTSCRIPTSHELL_QSTYLEOPTIONMENUITEM_H
#define QTSCRIPTSHELL_QSTYLEOPTIONMENUITEM_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionMenuItem : public QStyleOptionMenuItem
{
public:
    QtScriptShell_QStyleOptionMenuItem();
    QtScriptShell_QStyleOptionMenuItem(const QStyleOptionMenuItem&  other);
    QtScriptShell_QStyleOptionMenuItem(int  version);
    ~QtScriptShell_QStyleOptionMenuItem();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONMENUITEM_H
