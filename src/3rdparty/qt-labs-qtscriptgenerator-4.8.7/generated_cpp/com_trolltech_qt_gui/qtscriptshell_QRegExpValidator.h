#ifndef QTSCRIPTSHELL_QREGEXPVALIDATOR_H
#define QTSCRIPTSHELL_QREGEXPVALIDATOR_H

#include <qvalidator.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QRegExpValidator : public QRegExpValidator
{
public:
    QtScriptShell_QRegExpValidator(QObject*  parent = 0);
    QtScriptShell_QRegExpValidator(const QRegExp&  rx, QObject*  parent = 0);
    ~QtScriptShell_QRegExpValidator();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fixup(QString&  arg__1) const;
    void timerEvent(QTimerEvent*  arg__1);
    QValidator::State  validate(QString&  input, int&  pos) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QREGEXPVALIDATOR_H
