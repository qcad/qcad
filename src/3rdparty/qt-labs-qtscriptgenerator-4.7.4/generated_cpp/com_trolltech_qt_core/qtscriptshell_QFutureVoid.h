#ifndef QTSCRIPTSHELL_QFUTUREVOID_H
#define QTSCRIPTSHELL_QFUTUREVOID_H

#include <qtscriptconcurrent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFutureVoid : public QtScriptVoidFuture
{
public:
    QtScriptShell_QFutureVoid();
    ~QtScriptShell_QFutureVoid();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFUTUREVOID_H
