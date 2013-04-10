#ifndef QTSCRIPTSHELL_QUNDOGROUP_H
#define QTSCRIPTSHELL_QUNDOGROUP_H

#include <qundogroup.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QUndoGroup : public QUndoGroup
{
public:
    QtScriptShell_QUndoGroup(QObject*  parent = 0);
    ~QtScriptShell_QUndoGroup();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QUNDOGROUP_H
