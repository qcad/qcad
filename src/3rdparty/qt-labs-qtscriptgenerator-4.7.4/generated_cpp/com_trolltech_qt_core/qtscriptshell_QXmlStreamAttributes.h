#ifndef QTSCRIPTSHELL_QXMLSTREAMATTRIBUTES_H
#define QTSCRIPTSHELL_QXMLSTREAMATTRIBUTES_H

#include <qxmlstream.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlStreamAttributes : public QXmlStreamAttributes
{
public:
    QtScriptShell_QXmlStreamAttributes();
    ~QtScriptShell_QXmlStreamAttributes();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLSTREAMATTRIBUTES_H
