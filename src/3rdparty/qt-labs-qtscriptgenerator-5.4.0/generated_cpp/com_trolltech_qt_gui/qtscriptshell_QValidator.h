#ifndef QTSCRIPTSHELL_QVALIDATOR_H
#define QTSCRIPTSHELL_QVALIDATOR_H

#include <qvalidator.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QValidator : public QValidator
{
public:
    QtScriptShell_QValidator(QObject*  parent = 0);
    ~QtScriptShell_QValidator();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fixup(QString&  arg__1) const;
    void timerEvent(QTimerEvent*  arg__1);
    QValidator::State  validate(QString&  arg__1, int&  arg__2) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QVALIDATOR_H
