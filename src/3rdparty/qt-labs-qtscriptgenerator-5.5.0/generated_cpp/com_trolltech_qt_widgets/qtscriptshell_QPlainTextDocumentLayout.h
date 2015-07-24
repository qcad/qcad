#ifndef QTSCRIPTSHELL_QPLAINTEXTDOCUMENTLAYOUT_H
#define QTSCRIPTSHELL_QPLAINTEXTDOCUMENTLAYOUT_H

#include <qplaintextedit.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QPlainTextDocumentLayout : public QPlainTextDocumentLayout
{
public:
    QtScriptShell_QPlainTextDocumentLayout(QTextDocument*  document);
    ~QtScriptShell_QPlainTextDocumentLayout();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QPLAINTEXTDOCUMENTLAYOUT_H
