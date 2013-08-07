#ifndef QTSCRIPTSHELL_QTEXTDOCUMENT_H
#define QTSCRIPTSHELL_QTEXTDOCUMENT_H

#include <qtextdocument.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextDocument : public QTextDocument
{
public:
    QtScriptShell_QTextDocument(QObject*  parent = 0);
    QtScriptShell_QTextDocument(const QString&  text, QObject*  parent = 0);
    ~QtScriptShell_QTextDocument();

    void childEvent(QChildEvent*  arg__1);
    void clear();
    QTextObject*  createObject(const QTextFormat&  f);
    void customEvent(QEvent*  arg__1);
    bool  event(QEvent*  arg__1);
    bool  eventFilter(QObject*  arg__1, QEvent*  arg__2);
    QVariant  loadResource(int  type, const QUrl&  name);
    void timerEvent(QTimerEvent*  arg__1);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTDOCUMENT_H
