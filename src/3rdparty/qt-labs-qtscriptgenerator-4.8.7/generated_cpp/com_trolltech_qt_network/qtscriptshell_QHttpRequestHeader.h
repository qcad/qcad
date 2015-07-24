#ifndef QTSCRIPTSHELL_QHTTPREQUESTHEADER_H
#define QTSCRIPTSHELL_QHTTPREQUESTHEADER_H

#include <qhttp.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QHttpRequestHeader : public QHttpRequestHeader
{
public:
    QtScriptShell_QHttpRequestHeader();
    QtScriptShell_QHttpRequestHeader(const QHttpRequestHeader&  header);
    QtScriptShell_QHttpRequestHeader(const QString&  method, const QString&  path, int  majorVer = 1, int  minorVer = 1);
    QtScriptShell_QHttpRequestHeader(const QString&  str);
    ~QtScriptShell_QHttpRequestHeader();

    int  majorVersion() const;
    int  minorVersion() const;
    bool  parseLine(const QString&  line, int  number);
    QString  toString() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHTTPREQUESTHEADER_H
