#ifndef QTSCRIPTSHELL_QTEXTTABLECELLFORMAT_H
#define QTSCRIPTSHELL_QTEXTTABLECELLFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextTableCellFormat : public QTextTableCellFormat
{
public:
    QtScriptShell_QTextTableCellFormat();
    QtScriptShell_QTextTableCellFormat(const QTextFormat&  fmt);
    ~QtScriptShell_QTextTableCellFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTTABLECELLFORMAT_H
