#ifndef QTSCRIPTSHELL_QDRAG_H
#define QTSCRIPTSHELL_QDRAG_H

#include <qdrag.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QDrag : public QDrag
{
public:
    QtScriptShell_QDrag(QObject*  dragSource);
    ~QtScriptShell_QDrag();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QDRAG_H
