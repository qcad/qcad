#ifndef QTSCRIPTSHELL_QSYSTEMTRAYICON_H
#define QTSCRIPTSHELL_QSYSTEMTRAYICON_H

#include <qsystemtrayicon.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSystemTrayIcon : public QSystemTrayIcon
{
public:
    QtScriptShell_QSystemTrayIcon(QObject*  parent = 0);
    QtScriptShell_QSystemTrayIcon(const QIcon&  icon, QObject*  parent = 0);
    ~QtScriptShell_QSystemTrayIcon();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  event);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSYSTEMTRAYICON_H
