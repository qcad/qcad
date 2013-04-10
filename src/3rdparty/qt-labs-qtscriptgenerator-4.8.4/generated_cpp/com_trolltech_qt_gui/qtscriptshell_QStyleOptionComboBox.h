#ifndef QTSCRIPTSHELL_QSTYLEOPTIONCOMBOBOX_H
#define QTSCRIPTSHELL_QSTYLEOPTIONCOMBOBOX_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStyleOptionComboBox : public QStyleOptionComboBox
{
public:
    QtScriptShell_QStyleOptionComboBox();
    QtScriptShell_QStyleOptionComboBox(const QStyleOptionComboBox&  other);
    QtScriptShell_QStyleOptionComboBox(int  version);
    ~QtScriptShell_QStyleOptionComboBox();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONCOMBOBOX_H
