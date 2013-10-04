#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTABV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTABV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionTabV2 : public QStyleOptionTabV2
{
public:
    QtScriptShell_QStyleOptionTabV2();
    QtScriptShell_QStyleOptionTabV2(const QStyleOptionTab&  other);
    QtScriptShell_QStyleOptionTabV2(const QStyleOptionTabV2&  other);
    QtScriptShell_QStyleOptionTabV2(int  version);
    ~QtScriptShell_QStyleOptionTabV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTABV2_H
