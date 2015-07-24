#ifndef QTSCRIPTSHELL_QSTYLEOPTIONPROGRESSBAR_H
#define QTSCRIPTSHELL_QSTYLEOPTIONPROGRESSBAR_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionProgressBar : public QStyleOptionProgressBar
{
public:
    QtScriptShell_QStyleOptionProgressBar();
    QtScriptShell_QStyleOptionProgressBar(const QStyleOptionProgressBar&  other);
    QtScriptShell_QStyleOptionProgressBar(int  version);
    ~QtScriptShell_QStyleOptionProgressBar();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONPROGRESSBAR_H
