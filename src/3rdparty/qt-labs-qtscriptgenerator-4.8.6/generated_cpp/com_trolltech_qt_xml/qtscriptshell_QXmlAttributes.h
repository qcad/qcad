#ifndef QTSCRIPTSHELL_QXMLATTRIBUTES_H
#define QTSCRIPTSHELL_QXMLATTRIBUTES_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlAttributes : public QXmlAttributes
{
public:
    QtScriptShell_QXmlAttributes();
    ~QtScriptShell_QXmlAttributes();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLATTRIBUTES_H
