#ifndef QTSCRIPTSHELL_QTEXTIMAGEFORMAT_H
#define QTSCRIPTSHELL_QTEXTIMAGEFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QTextImageFormat : public QTextImageFormat
{
public:
    QtScriptShell_QTextImageFormat();
    QtScriptShell_QTextImageFormat(const QTextFormat&  format);
    ~QtScriptShell_QTextImageFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTIMAGEFORMAT_H
