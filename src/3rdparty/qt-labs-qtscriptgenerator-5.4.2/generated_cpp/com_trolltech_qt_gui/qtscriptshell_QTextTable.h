#ifndef QTSCRIPTSHELL_QTEXTTABLE_H
#define QTSCRIPTSHELL_QTEXTTABLE_H

#include <qtexttable.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextTable : public QTextTable
{
public:
    QtScriptShell_QTextTable(QTextDocument*  doc);
    ~QtScriptShell_QTextTable();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTTABLE_H
