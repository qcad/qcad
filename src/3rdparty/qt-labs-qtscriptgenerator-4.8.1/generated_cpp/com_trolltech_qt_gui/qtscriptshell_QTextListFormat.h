#ifndef QTSCRIPTSHELL_QTEXTLISTFORMAT_H
#define QTSCRIPTSHELL_QTEXTLISTFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextListFormat : public QTextListFormat
{
public:
    QtScriptShell_QTextListFormat();
    QtScriptShell_QTextListFormat(const QTextFormat&  fmt);
    ~QtScriptShell_QTextListFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTLISTFORMAT_H
