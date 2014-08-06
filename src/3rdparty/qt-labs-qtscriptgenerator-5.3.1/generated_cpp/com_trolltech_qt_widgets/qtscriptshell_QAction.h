#ifndef QTSCRIPTSHELL_QACTION_H
#define QTSCRIPTSHELL_QACTION_H

#include <qaction.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QAction : public QAction
{
public:
    QtScriptShell_QAction(QObject*  parent);
    QtScriptShell_QAction(const QIcon&  icon, const QString&  text, QObject*  parent);
    QtScriptShell_QAction(const QString&  text, QObject*  parent);
    ~QtScriptShell_QAction();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACTION_H
