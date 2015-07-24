#ifndef QTSCRIPTSHELL_QACCESSIBLEPLUGIN_H
#define QTSCRIPTSHELL_QACCESSIBLEPLUGIN_H

#include <qaccessibleplugin.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAccessiblePlugin : public QAccessiblePlugin
{
public:
    QtScriptShell_QAccessiblePlugin(QObject*  parent = 0);
    ~QtScriptShell_QAccessiblePlugin();

    void childEvent(QChildEvent*  arg__1);
    QAccessibleInterface*  create(const QString&  key, QObject*  object);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QStringList  keys() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QACCESSIBLEPLUGIN_H
