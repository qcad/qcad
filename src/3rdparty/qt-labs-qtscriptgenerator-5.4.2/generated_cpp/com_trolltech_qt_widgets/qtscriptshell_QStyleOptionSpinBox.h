#ifndef QTSCRIPTSHELL_QSTYLEOPTIONSPINBOX_H
#define QTSCRIPTSHELL_QSTYLEOPTIONSPINBOX_H

#include <qstyleoption.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QStyleOptionSpinBox : public QStyleOptionSpinBox
{
public:
    QtScriptShell_QStyleOptionSpinBox();
    QtScriptShell_QStyleOptionSpinBox(const QStyleOptionSpinBox&  other);
    QtScriptShell_QStyleOptionSpinBox(int  version);
    ~QtScriptShell_QStyleOptionSpinBox();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEOPTIONSPINBOX_H
