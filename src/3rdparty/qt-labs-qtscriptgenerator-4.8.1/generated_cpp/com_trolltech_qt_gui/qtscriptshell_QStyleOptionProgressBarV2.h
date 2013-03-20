#ifndef QTSCRIPTSHELL_QSTYLEOPTIONPROGRESSBARV2_H
#define QTSCRIPTSHELL_QSTYLEOPTIONPROGRESSBARV2_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionProgressBarV2 : public QStyleOptionProgressBarV2
{
public:
    QtScriptShell_QStyleOptionProgressBarV2();
    QtScriptShell_QStyleOptionProgressBarV2(const QStyleOptionProgressBar&  other);
    QtScriptShell_QStyleOptionProgressBarV2(const QStyleOptionProgressBarV2&  other);
    QtScriptShell_QStyleOptionProgressBarV2(int  version);
    ~QtScriptShell_QStyleOptionProgressBarV2();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONPROGRESSBARV2_H
