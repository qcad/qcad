#ifndef QTSCRIPTSHELL_QUNDOSTACK_H
#define QTSCRIPTSHELL_QUNDOSTACK_H

#include <qundostack.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QUndoStack : public QUndoStack
{
public:
    QtScriptShell_QUndoStack(QObject*  parent = 0);
    ~QtScriptShell_QUndoStack();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUNDOSTACK_H
