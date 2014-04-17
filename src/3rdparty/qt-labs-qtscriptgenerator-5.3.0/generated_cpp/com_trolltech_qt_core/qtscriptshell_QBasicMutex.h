#ifndef QTSCRIPTSHELL_QBASICMUTEX_H
#define QTSCRIPTSHELL_QBASICMUTEX_H

#include <qmutex.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QBasicMutex : public QBasicMutex
{
public:
    QtScriptShell_QBasicMutex();
    ~QtScriptShell_QBasicMutex();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBASICMUTEX_H
