#ifndef QTSCRIPTSHELL_QHTTPHEADER_H
#define QTSCRIPTSHELL_QHTTPHEADER_H

#include <qhttp.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QHttpHeader : public QHttpHeader
{
public:
    QtScriptShell_QHttpHeader();
    QtScriptShell_QHttpHeader(const QHttpHeader&  header);
    QtScriptShell_QHttpHeader(const QString&  str);
    ~QtScriptShell_QHttpHeader();

    int  majorVersion() const;
    int  minorVersion() const;
    bool  parseLine(const QString&  line, int  number);
    QString  toString() const;

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QHTTPHEADER_H
