#ifndef QTSCRIPTSHELL_QFILESYSTEMWATCHER_H
#define QTSCRIPTSHELL_QFILESYSTEMWATCHER_H

#include <qfilesystemwatcher.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QFileSystemWatcher : public QFileSystemWatcher
{
public:
    QtScriptShell_QFileSystemWatcher(QObject*  parent = 0);
    QtScriptShell_QFileSystemWatcher(const QStringList&  paths, QObject*  parent = 0);
    ~QtScriptShell_QFileSystemWatcher();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QFILESYSTEMWATCHER_H
