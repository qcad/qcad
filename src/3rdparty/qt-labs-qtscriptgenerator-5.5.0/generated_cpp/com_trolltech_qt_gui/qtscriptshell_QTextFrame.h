#ifndef QTSCRIPTSHELL_QTEXTFRAME_H
#define QTSCRIPTSHELL_QTEXTFRAME_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextFrame : public QTextFrame
{
public:
    QtScriptShell_QTextFrame(QTextDocument*  doc);
    ~QtScriptShell_QTextFrame();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTFRAME_H
