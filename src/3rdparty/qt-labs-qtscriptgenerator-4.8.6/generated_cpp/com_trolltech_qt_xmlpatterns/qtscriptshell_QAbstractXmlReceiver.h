#ifndef QTSCRIPTSHELL_QABSTRACTXMLRECEIVER_H
#define QTSCRIPTSHELL_QABSTRACTXMLRECEIVER_H

#include <qabstractxmlreceiver.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QAbstractXmlReceiver : public QAbstractXmlReceiver
{
public:
    QtScriptShell_QAbstractXmlReceiver();
    ~QtScriptShell_QAbstractXmlReceiver();

    void atomicValue(const QVariant&  value);
    void attribute(const QXmlName&  name, const QStringRef&  value);
    void characters(const QStringRef&  value);
    void comment(const QString&  value);
    void endDocument();
    void endElement();
    void endOfSequence();
    void namespaceBinding(const QXmlName&  name);
    void processingInstruction(const QXmlName&  target, const QString&  value);
    void startDocument();
    void startElement(const QXmlName&  name);
    void startOfSequence();
    void whitespaceOnly(const QStringRef&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QABSTRACTXMLRECEIVER_H
