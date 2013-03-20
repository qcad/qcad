#ifndef QTSCRIPTSHELL_QINPUTCONTEXTPLUGIN_H
#define QTSCRIPTSHELL_QINPUTCONTEXTPLUGIN_H

#include <qinputcontextplugin.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QInputContextPlugin : public QInputContextPlugin
{
public:
    QtScriptShell_QInputContextPlugin(QObject*  parent = 0);
    ~QtScriptShell_QInputContextPlugin();

    void childEvent(QChildEvent*  arg__1);
    QInputContext*  create(const QString&  key);
    void customEvent(QEvent*  arg__1);
    QString  description(const QString&  key);
    QString  displayName(const QString&  key);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QStringList  keys() const;
    QStringList  languages(const QString&  key);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QINPUTCONTEXTPLUGIN_H
