#ifndef QTSCRIPTSHELL_QSTYLEOPTIONGROUPBOX_H
#define QTSCRIPTSHELL_QSTYLEOPTIONGROUPBOX_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionGroupBox : public QStyleOptionGroupBox
{
public:
    QtScriptShell_QStyleOptionGroupBox();
    QtScriptShell_QStyleOptionGroupBox(const QStyleOptionGroupBox&  other);
    QtScriptShell_QStyleOptionGroupBox(int  version);
    ~QtScriptShell_QStyleOptionGroupBox();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONGROUPBOX_H
