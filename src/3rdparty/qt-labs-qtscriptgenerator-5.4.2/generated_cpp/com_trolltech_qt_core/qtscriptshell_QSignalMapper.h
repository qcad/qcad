#ifndef QTSCRIPTSHELL_QSIGNALMAPPER_H
#define QTSCRIPTSHELL_QSIGNALMAPPER_H

#include <qsignalmapper.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSignalMapper : public QSignalMapper
{
public:
    QtScriptShell_QSignalMapper(QObject*  parent = 0);
    ~QtScriptShell_QSignalMapper();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSIGNALMAPPER_H
