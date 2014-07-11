#ifndef QTSCRIPTSHELL_QPAINTENGINESTATE_H
#define QTSCRIPTSHELL_QPAINTENGINESTATE_H

#include <qpaintengine.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPaintEngineState : public QPaintEngineState
{
public:
    QtScriptShell_QPaintEngineState();
    ~QtScriptShell_QPaintEngineState();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPAINTENGINESTATE_H
