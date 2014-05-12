#ifndef QTSCRIPTSHELL_QSTYLEOPTIONSIZEGRIP_H
#define QTSCRIPTSHELL_QSTYLEOPTIONSIZEGRIP_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionSizeGrip : public QStyleOptionSizeGrip
{
public:
    QtScriptShell_QStyleOptionSizeGrip();
    QtScriptShell_QStyleOptionSizeGrip(const QStyleOptionSizeGrip&  other);
    QtScriptShell_QStyleOptionSizeGrip(int  version);
    ~QtScriptShell_QStyleOptionSizeGrip();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONSIZEGRIP_H
