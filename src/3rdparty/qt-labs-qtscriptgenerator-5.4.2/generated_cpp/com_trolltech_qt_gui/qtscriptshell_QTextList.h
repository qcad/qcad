#ifndef QTSCRIPTSHELL_QTEXTLIST_H
#define QTSCRIPTSHELL_QTEXTLIST_H

#include <qtextlist.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextList : public QTextList
{
public:
    QtScriptShell_QTextList(QTextDocument*  doc);
    ~QtScriptShell_QTextList();

    void blockFormatChanged(const QTextBlock&  block);
    void blockInserted(const QTextBlock&  block);
    void blockRemoved(const QTextBlock&  block);
    void childEvent(QChildEvent*  arg__1);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTLIST_H
