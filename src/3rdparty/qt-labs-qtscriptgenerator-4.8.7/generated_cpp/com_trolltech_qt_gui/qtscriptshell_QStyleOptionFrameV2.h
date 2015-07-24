#ifndef QTSCRIPTSHELL_QSTYLEOPTIONFRAMEV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONFRAMEV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionFrameV2 : public QStyleOptionFrameV2
{
public:
    QtScriptShell_QStyleOptionFrameV2();
    QtScriptShell_QStyleOptionFrameV2(const QStyleOptionFrame&  other);
    QtScriptShell_QStyleOptionFrameV2(const QStyleOptionFrameV2&  other);
    QtScriptShell_QStyleOptionFrameV2(int  version);
    ~QtScriptShell_QStyleOptionFrameV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONFRAMEV2_H
