#ifndef QTSCRIPTSHELL_QINTVALIDATOR_H
#define QTSCRIPTSHELL_QINTVALIDATOR_H

#include <qvalidator.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QIntValidator : public QIntValidator
{
public:
    QtScriptShell_QIntValidator(QObject*  parent = 0);
    QtScriptShell_QIntValidator(int  bottom, int  top, QObject*  parent);
    ~QtScriptShell_QIntValidator();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fixup(QString&  input) const;
    void setRange(int  bottom, int  top);
    void timerEvent(QTimerEvent*  arg__1);
    QValidator::State  validate(QString&  arg__1, int&  arg__2) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QINTVALIDATOR_H
