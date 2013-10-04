#ifndef QTSCRIPTSHELL_QSTYLEPLUGIN_H
#define QTSCRIPTSHELL_QSTYLEPLUGIN_H

#include <qstyleplugin.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QStylePlugin : public QStylePlugin
{
public:
    QtScriptShell_QStylePlugin(QObject*  parent = 0);
    ~QtScriptShell_QStylePlugin();

    void childEvent(QChildEvent*  arg__1);
    QStyle*  create(const QString&  key);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QStringList  keys() const;
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSTYLEPLUGIN_H
