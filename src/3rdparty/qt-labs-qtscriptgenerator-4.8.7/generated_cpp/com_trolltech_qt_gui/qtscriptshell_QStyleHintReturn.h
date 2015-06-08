#ifndef QTSCRIPTSHELL_QSTYLEHINTRETURN_H
#define QTSCRIPTSHELL_QSTYLEHINTRETURN_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleHintReturn : public QStyleHintReturn
{
public:
    QtScriptShell_QStyleHintReturn(int  version = QStyleOption::Version, int  type = SH_Default);
    ~QtScriptShell_QStyleHintReturn();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEHINTRETURN_H
