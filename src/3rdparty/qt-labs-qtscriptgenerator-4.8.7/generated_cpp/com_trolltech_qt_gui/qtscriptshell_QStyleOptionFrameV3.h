#ifndef QTSCRIPTSHELL_QSTYLEOPTIONFRAMEV3_H
#define QTSCRIPTSHELL_QSTYLEOPTIONFRAMEV3_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionFrameV3 : public QStyleOptionFrameV3
{
public:
    QtScriptShell_QStyleOptionFrameV3();
    QtScriptShell_QStyleOptionFrameV3(const QStyleOptionFrame&  other);
    QtScriptShell_QStyleOptionFrameV3(const QStyleOptionFrameV3&  other);
    QtScriptShell_QStyleOptionFrameV3(int  version);
    ~QtScriptShell_QStyleOptionFrameV3();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONFRAMEV3_H
