#ifndef QTSCRIPTSHELL_QTEXTOBJECT_H
#define QTSCRIPTSHELL_QTEXTOBJECT_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextObject : public QTextObject
{
public:
    QtScriptShell_QTextObject(QTextDocument*  doc);
    ~QtScriptShell_QTextObject();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTOBJECT_H
