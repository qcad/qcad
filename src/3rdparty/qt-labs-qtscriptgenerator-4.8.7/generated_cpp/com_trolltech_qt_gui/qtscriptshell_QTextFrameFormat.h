#ifndef QTSCRIPTSHELL_QTEXTFRAMEFORMAT_H
#define QTSCRIPTSHELL_QTEXTFRAMEFORMAT_H

#include <qtextformat.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextFrameFormat : public QTextFrameFormat
{
public:
    QtScriptShell_QTextFrameFormat();
    QtScriptShell_QTextFrameFormat(const QTextFormat&  fmt);
    ~QtScriptShell_QTextFrameFormat();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTFRAMEFORMAT_H
