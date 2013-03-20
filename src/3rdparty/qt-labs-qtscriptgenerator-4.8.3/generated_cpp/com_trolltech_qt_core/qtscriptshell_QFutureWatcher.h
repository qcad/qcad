#ifndef QTSCRIPTSHELL_QFUTUREWATCHER_H
#define QTSCRIPTSHELL_QFUTUREWATCHER_H

#include <qtscriptconcurrent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFutureWatcher : public QtScriptFutureWatcher
{
public:
    QtScriptShell_QFutureWatcher();
    ~QtScriptShell_QFutureWatcher();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFUTUREWATCHER_H
