#ifndef QTSCRIPTSHELL_QACTIONGROUP_H
#define QTSCRIPTSHELL_QACTIONGROUP_H

#include <qactiongroup.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QActionGroup : public QActionGroup
{
public:
    QtScriptShell_QActionGroup(QObject*  parent);
    ~QtScriptShell_QActionGroup();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACTIONGROUP_H
