#ifndef QTSCRIPTSHELL_QFUTUREWATCHERVOID_H
#define QTSCRIPTSHELL_QFUTUREWATCHERVOID_H

#include <qtscriptconcurrent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFutureWatcherVoid : public QtScriptVoidFutureWatcher
{
public:
    QtScriptShell_QFutureWatcherVoid();
    ~QtScriptShell_QFutureWatcherVoid();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFUTUREWATCHERVOID_H
