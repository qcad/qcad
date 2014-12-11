#ifndef QTSCRIPTSHELL_QPANGESTURE_H
#define QTSCRIPTSHELL_QPANGESTURE_H

#include <qgesture.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPanGesture : public QPanGesture
{
public:
    QtScriptShell_QPanGesture(QObject*  parent = 0);
    ~QtScriptShell_QPanGesture();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPANGESTURE_H
