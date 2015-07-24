#ifndef QTSCRIPTSHELL_QSTYLEOPTIONDOCKWIDGETV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONDOCKWIDGETV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionDockWidgetV2 : public QStyleOptionDockWidgetV2
{
public:
    QtScriptShell_QStyleOptionDockWidgetV2();
    QtScriptShell_QStyleOptionDockWidgetV2(const QStyleOptionDockWidget&  other);
    QtScriptShell_QStyleOptionDockWidgetV2(const QStyleOptionDockWidgetV2&  other);
    QtScriptShell_QStyleOptionDockWidgetV2(int  version);
    ~QtScriptShell_QStyleOptionDockWidgetV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONDOCKWIDGETV2_H
