#ifndef QTSCRIPTSHELL_QSTYLEOPTION_H
#define QTSCRIPTSHELL_QSTYLEOPTION_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOption : public QStyleOption
{
public:
    QtScriptShell_QStyleOption(const QStyleOption&  other);
    QtScriptShell_QStyleOption(int  version = QStyleOption::Version, int  type = SO_Default);
    ~QtScriptShell_QStyleOption();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTION_H
