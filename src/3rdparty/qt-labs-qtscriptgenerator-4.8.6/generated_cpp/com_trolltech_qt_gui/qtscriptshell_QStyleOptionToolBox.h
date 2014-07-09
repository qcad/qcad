#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTOOLBOX_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTOOLBOX_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionToolBox : public QStyleOptionToolBox
{
public:
    QtScriptShell_QStyleOptionToolBox();
    QtScriptShell_QStyleOptionToolBox(const QStyleOptionToolBox&  other);
    QtScriptShell_QStyleOptionToolBox(int  version);
    ~QtScriptShell_QStyleOptionToolBox();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTOOLBOX_H
