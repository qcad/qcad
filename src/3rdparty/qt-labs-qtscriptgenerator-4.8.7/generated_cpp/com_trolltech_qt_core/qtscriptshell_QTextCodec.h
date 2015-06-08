#ifndef QTSCRIPTSHELL_QTEXTCODEC_H
#define QTSCRIPTSHELL_QTEXTCODEC_H

#include <qtextcodec.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QTextCodec : public QTextCodec
{
public:
    QtScriptShell_QTextCodec();
    ~QtScriptShell_QTextCodec();

    QList<QByteArray >  aliases() const;
    QByteArray  convertFromUnicode(const QChar*  in, int  length, QTextCodec::ConverterState*  state) const;
    QString  convertToUnicode(const char*  in, int  length, QTextCodec::ConverterState*  state) const;
    int  mibEnum() const;
    QByteArray  name() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QTEXTCODEC_H
