#ifndef QTSCRIPTSHELL_QXMLFORMATTER_H
#define QTSCRIPTSHELL_QXMLFORMATTER_H

#include <qxmlformatter.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlFormatter : public QXmlFormatter
{
public:
    QtScriptShell_QXmlFormatter(const QXmlQuery&  query, QIODevice*  outputDevice);
    ~QtScriptShell_QXmlFormatter();

    void atomicValue(const QVariant&  value);
    void attribute(const QXmlName&  name, const QStringRef&  value);
    void characters(const QStringRef&  value);
    void comment(const QString&  value);
    void endDocument();
    void endElement();
    void endOfSequence();
    void namespaceBinding(const QXmlName&  nb);
    void processingInstruction(const QXmlName&  name, const QString&  value);
    void startDocument();
    void startElement(const QXmlName&  name);
    void startOfSequence();
    void whitespaceOnly(const QStringRef&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLFORMATTER_H
