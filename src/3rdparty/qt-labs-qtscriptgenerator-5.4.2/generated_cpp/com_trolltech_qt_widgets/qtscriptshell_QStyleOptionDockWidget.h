#ifndef QTSCRIPTSHELL_QSTYLEOPTIONDOCKWIDGET_H
#define QTSCRIPTSHELL_QSTYLEOPTIONDOCKWIDGET_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionDockWidget : public QStyleOptionDockWidget
{
public:
    QtScriptShell_QStyleOptionDockWidget();
    QtScriptShell_QStyleOptionDockWidget(const QStyleOptionDockWidget&  other);
    QtScriptShell_QStyleOptionDockWidget(int  version);
    ~QtScriptShell_QStyleOptionDockWidget();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONDOCKWIDGET_H
