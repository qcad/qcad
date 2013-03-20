#ifndef QTSCRIPTSHELL_QDOUBLEVALIDATOR_H
#define QTSCRIPTSHELL_QDOUBLEVALIDATOR_H

#include <qvalidator.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QDoubleValidator : public QDoubleValidator
{
public:
    QtScriptShell_QDoubleValidator(QObject*  parent = 0);
    QtScriptShell_QDoubleValidator(double  bottom, double  top, int  decimals, QObject*  parent = 0);
    ~QtScriptShell_QDoubleValidator();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void fixup(QString&  arg__1) const;
    void setRange(double  bottom, double  top, int  decimals = 0);
    void timerEvent(QTimerEvent*  arg__1);
    QValidator::State  validate(QString&  arg__1, int&  arg__2) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDOUBLEVALIDATOR_H
