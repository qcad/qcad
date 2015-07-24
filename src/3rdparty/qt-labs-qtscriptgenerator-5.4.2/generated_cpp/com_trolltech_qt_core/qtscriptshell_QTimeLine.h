#ifndef QTSCRIPTSHELL_QTIMELINE_H
#define QTSCRIPTSHELL_QTIMELINE_H

#include <qtimeline.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTimeLine : public QTimeLine
{
public:
    QtScriptShell_QTimeLine(int  duration = 1000, QObject*  parent = 0);
    ~QtScriptShell_QTimeLine();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  event);
    qreal  valueForTime(int  msec) const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTIMELINE_H
