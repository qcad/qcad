#ifndef QTSCRIPTSHELL_QSTYLEOPTIONTABV3_H
#define QTSCRIPTSHELL_QSTYLEOPTIONTABV3_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionTabV3 : public QStyleOptionTabV3
{
public:
    QtScriptShell_QStyleOptionTabV3();
    QtScriptShell_QStyleOptionTabV3(const QStyleOptionTab&  other);
    QtScriptShell_QStyleOptionTabV3(const QStyleOptionTabV2&  other);
    QtScriptShell_QStyleOptionTabV3(const QStyleOptionTabV3&  other);
    QtScriptShell_QStyleOptionTabV3(int  version);
    ~QtScriptShell_QStyleOptionTabV3();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONTABV3_H
