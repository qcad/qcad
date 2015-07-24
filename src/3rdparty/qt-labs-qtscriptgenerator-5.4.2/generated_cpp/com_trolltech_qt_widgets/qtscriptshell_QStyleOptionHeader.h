#ifndef QTSCRIPTSHELL_QSTYLEOPTIONHEADER_H
#define QTSCRIPTSHELL_QSTYLEOPTIONHEADER_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionHeader : public QStyleOptionHeader
{
public:
    QtScriptShell_QStyleOptionHeader();
    QtScriptShell_QStyleOptionHeader(const QStyleOptionHeader&  other);
    QtScriptShell_QStyleOptionHeader(int  version);
    ~QtScriptShell_QStyleOptionHeader();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONHEADER_H
