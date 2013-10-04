#ifndef QTSCRIPTSHELL_QACCESSIBLE2INTERFACE_H
#define QTSCRIPTSHELL_QACCESSIBLE2INTERFACE_H

#include <qaccessible2.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessible2Interface : public QAccessible2Interface
{
public:
    QtScriptShell_QAccessible2Interface();
    ~QtScriptShell_QAccessible2Interface();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLE2INTERFACE_H
