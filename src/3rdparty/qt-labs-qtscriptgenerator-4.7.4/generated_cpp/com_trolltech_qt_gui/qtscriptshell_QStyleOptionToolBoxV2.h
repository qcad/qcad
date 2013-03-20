#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTOOLBOXV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTOOLBOXV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionToolBoxV2 : public QStyleOptionToolBoxV2
{
public:
    QtScriptShell_QStyleOptionToolBoxV2();
    QtScriptShell_QStyleOptionToolBoxV2(const QStyleOptionToolBox&  other);
    QtScriptShell_QStyleOptionToolBoxV2(const QStyleOptionToolBoxV2&  other);
    QtScriptShell_QStyleOptionToolBoxV2(int  version);
    ~QtScriptShell_QStyleOptionToolBoxV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTOOLBOXV2_H
