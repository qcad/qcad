#ifndef QTSCRIPTSHELL_QSYNTAXHIGHLIGHTER_H
#define QTSCRIPTSHELL_QSYNTAXHIGHLIGHTER_H

#include <qsyntaxhighlighter.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSyntaxHighlighter : public QSyntaxHighlighter
{
public:
    QtScriptShell_QSyntaxHighlighter(QObject*  parent);
    QtScriptShell_QSyntaxHighlighter(QTextDocument*  parent);
    ~QtScriptShell_QSyntaxHighlighter();

    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void highlightBlock(const QString&  text);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSYNTAXHIGHLIGHTER_H
