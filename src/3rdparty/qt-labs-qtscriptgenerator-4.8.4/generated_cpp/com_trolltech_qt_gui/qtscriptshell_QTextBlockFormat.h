#ifndef QTSCRIPTSHELL_QTEXTBLOCKFORMAT_H
#define QTSCRIPTSHELL_QTEXTBLOCKFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextBlockFormat : public QTextBlockFormat
{
public:
    QtScriptShell_QTextBlockFormat();
    QtScriptShell_QTextBlockFormat(const QTextFormat&  fmt);
    ~QtScriptShell_QTextBlockFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTBLOCKFORMAT_H
