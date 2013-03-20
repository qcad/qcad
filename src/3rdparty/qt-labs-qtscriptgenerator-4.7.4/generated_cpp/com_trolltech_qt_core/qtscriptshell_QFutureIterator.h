#ifndef QTSCRIPTSHELL_QFUTUREITERATOR_H
#define QTSCRIPTSHELL_QFUTUREITERATOR_H

#include <qtscriptconcurrent.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QFutureIterator : public QtScriptFutureIterator
{
public:
    QtScriptShell_QFutureIterator();
    ~QtScriptShell_QFutureIterator();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFUTUREITERATOR_H
