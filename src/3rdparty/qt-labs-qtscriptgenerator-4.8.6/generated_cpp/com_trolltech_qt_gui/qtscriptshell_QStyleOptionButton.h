#ifndef QTSCRIPTSHELL_QSTYLEOPTIONBUTTON_H
#define QTSCRIPTSHELL_QSTYLEOPTIONBUTTON_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionButton : public QStyleOptionButton
{
public:
    QtScriptShell_QStyleOptionButton();
    QtScriptShell_QStyleOptionButton(const QStyleOptionButton&  other);
    QtScriptShell_QStyleOptionButton(int  version);
    ~QtScriptShell_QStyleOptionButton();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONBUTTON_H
