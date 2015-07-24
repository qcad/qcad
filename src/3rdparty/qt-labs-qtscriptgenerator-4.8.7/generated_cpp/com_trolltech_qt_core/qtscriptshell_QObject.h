#ifndef QTSCRIPTSHELL_QOBJECT_H
#define QTSCRIPTSHELL_QOBJECT_H

#include <qobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QObject : public QObject
{
public:
    QtScriptShell_QObject(QObject*  parent = 0);
    ~QtScriptShell_QObject();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QOBJECT_H
