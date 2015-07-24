#ifndef QTSCRIPTSHELL_QHTTPRESPONSEHEADER_H
#define QTSCRIPTSHELL_QHTTPRESPONSEHEADER_H

#include <qhttp.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QHttpResponseHeader : public QHttpResponseHeader
{
public:
    QtScriptShell_QHttpResponseHeader();
    QtScriptShell_QHttpResponseHeader(const QHttpResponseHeader&  header);
    QtScriptShell_QHttpResponseHeader(const QString&  str);
    QtScriptShell_QHttpResponseHeader(int  code, const QString&  text = QString(), int  majorVer = 1, int  minorVer = 1);
    ~QtScriptShell_QHttpResponseHeader();

    int  majorVersion() const;
    int  minorVersion() const;
    bool  parseLine(const QString&  line, int  number);
    QString  toString() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHTTPRESPONSEHEADER_H
