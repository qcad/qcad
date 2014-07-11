#ifndef QTSCRIPTSHELL_QFUTURESYNCHRONIZER_H
#define QTSCRIPTSHELL_QFUTURESYNCHRONIZER_H

#include <qtscriptconcurrent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFutureSynchronizer : public QtScriptFutureSynchronizer
{
public:
    QtScriptShell_QFutureSynchronizer();
    ~QtScriptShell_QFutureSynchronizer();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFUTURESYNCHRONIZER_H
