#ifndef QTSCRIPTSHELL_QPINCHGESTURE_H
#define QTSCRIPTSHELL_QPINCHGESTURE_H

#include <qgesture.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QPinchGesture : public QPinchGesture
{
public:
    QtScriptShell_QPinchGesture(QObject*  parent = 0);
    ~QtScriptShell_QPinchGesture();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPINCHGESTURE_H
