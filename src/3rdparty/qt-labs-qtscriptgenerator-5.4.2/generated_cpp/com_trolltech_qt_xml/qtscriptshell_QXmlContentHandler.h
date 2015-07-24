#ifndef QTSCRIPTSHELL_QXMLCONTENTHANDLER_H
#define QTSCRIPTSHELL_QXMLCONTENTHANDLER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QXmlContentHandler : public QXmlContentHandler
{
public:
    QtScriptShell_QXmlContentHandler();
    ~QtScriptShell_QXmlContentHandler();

    bool  characters(const QString&  ch);
    bool  endDocument();
    bool  endElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName);
    bool  endPrefixMapping(const QString&  prefix);
    QString  errorString() const;
    bool  ignorableWhitespace(const QString&  ch);
    bool  processingInstruction(const QString&  target, const QString&  data);
    void setDocumentLocator(QXmlLocator*  locator);
    bool  skippedEntity(const QString&  name);
    bool  startDocument();
    bool  startElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName, const QXmlAttributes&  atts);
    bool  startPrefixMapping(const QString&  prefix, const QString&  uri);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLCONTENTHANDLER_H
