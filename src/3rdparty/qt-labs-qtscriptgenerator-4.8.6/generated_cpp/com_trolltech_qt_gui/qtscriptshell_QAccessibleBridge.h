#ifndef QTSCRIPTSHELL_QACCESSIBLEBRIDGE_H
#define QTSCRIPTSHELL_QACCESSIBLEBRIDGE_H

#include <qaccessiblebridge.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessibleBridge : public QAccessibleBridge
{
public:
    QtScriptShell_QAccessibleBridge();
    ~QtScriptShell_QAccessibleBridge();

    void notifyAccessibilityUpdate(int  arg__1, QAccessibleInterface*  arg__2, int  arg__3);
    void setRootObject(QAccessibleInterface*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEBRIDGE_H
