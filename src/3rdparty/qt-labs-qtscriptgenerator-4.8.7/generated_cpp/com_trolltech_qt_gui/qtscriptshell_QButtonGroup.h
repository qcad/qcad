#ifndef QTSCRIPTSHELL_QBUTTONGROUP_H
#define QTSCRIPTSHELL_QBUTTONGROUP_H

#include <qbuttongroup.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QButtonGroup : public QButtonGroup
{
public:
    QtScriptShell_QButtonGroup(QObject*  parent = 0);
    ~QtScriptShell_QButtonGroup();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QBUTTONGROUP_H
