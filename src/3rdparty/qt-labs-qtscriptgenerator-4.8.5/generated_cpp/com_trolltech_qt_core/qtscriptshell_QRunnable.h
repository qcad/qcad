#ifndef QTSCRIPTSHELL_QRUNNABLE_H
#define QTSCRIPTSHELL_QRUNNABLE_H

#include <qrunnable.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QRunnable : public QRunnable
{
public:
    QtScriptShell_QRunnable();
    ~QtScriptShell_QRunnable();

    void run();

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QRUNNABLE_H
