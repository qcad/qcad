#ifndef QTSCRIPTSHELL_QTEXTTABLEFORMAT_H
#define QTSCRIPTSHELL_QTEXTTABLEFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextTableFormat : public QTextTableFormat
{
public:
    QtScriptShell_QTextTableFormat();
    QtScriptShell_QTextTableFormat(const QTextFormat&  fmt);
    ~QtScriptShell_QTextTableFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTTABLEFORMAT_H
