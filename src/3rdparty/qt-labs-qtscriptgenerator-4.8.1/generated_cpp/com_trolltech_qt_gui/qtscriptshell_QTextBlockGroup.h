#ifndef QTSCRIPTSHELL_QTEXTBLOCKGROUP_H
#define QTSCRIPTSHELL_QTEXTBLOCKGROUP_H

#include <qtextobject.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextBlockGroup : public QTextBlockGroup
{
public:
    QtScriptShell_QTextBlockGroup(QTextDocument*  doc);
    ~QtScriptShell_QTextBlockGroup();

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

#endif // QTSCRIPTSHELL_QTEXTBLOCKGROUP_H
