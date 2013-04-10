#ifndef QTSCRIPTSHELL_QTEXTCHARFORMAT_H
#define QTSCRIPTSHELL_QTEXTCHARFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextCharFormat : public QTextCharFormat
{
public:
    QtScriptShell_QTextCharFormat();
    QtScriptShell_QTextCharFormat(const QTextFormat&  fmt);
    ~QtScriptShell_QTextCharFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTCHARFORMAT_H
