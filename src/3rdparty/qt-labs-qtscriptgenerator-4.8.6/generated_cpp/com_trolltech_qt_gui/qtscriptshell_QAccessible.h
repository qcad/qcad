#ifndef QTSCRIPTSHELL_QACCESSIBLE_H
#define QTSCRIPTSHELL_QACCESSIBLE_H

#include <qaccessible.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessible : public QAccessible
{
public:
    QtScriptShell_QAccessible();
    ~QtScriptShell_QAccessible();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLE_H
