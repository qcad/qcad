#ifndef QTSCRIPTSHELL_QFUTURE_H
#define QTSCRIPTSHELL_QFUTURE_H

#include <qtscriptconcurrent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFuture : public QtScriptFuture
{
public:
    QtScriptShell_QFuture();
    ~QtScriptShell_QFuture();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFUTURE_H
