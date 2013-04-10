#ifndef QTSCRIPTSHELL_QXMLDEFAULTHANDLER_H
#define QTSCRIPTSHELL_QXMLDEFAULTHANDLER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlDefaultHandler : public QXmlDefaultHandler
{
public:
    QtScriptShell_QXmlDefaultHandler();
    ~QtScriptShell_QXmlDefaultHandler();

    bool  attributeDecl(const QString&  eName, const QString&  aName, const QString&  type, const QString&  valueDefault, const QString&  value);
    bool  characters(const QString&  ch);
    bool  comment(const QString&  ch);
    bool  endCDATA();
    bool  endDTD();
    bool  endDocument();
    bool  endElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName);
    bool  endEntity(const QString&  name);
    bool  endPrefixMapping(const QString&  prefix);
    bool  error(const QXmlParseException&  exception);
    QString  errorString() const;
    bool  externalEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId);
    bool  fatalError(const QXmlParseException&  exception);
    bool  ignorableWhitespace(const QString&  ch);
    bool  internalEntityDecl(const QString&  name, const QString&  value);
    bool  notationDecl(const QString&  name, const QString&  publicId, const QString&  systemId);
    bool  processingInstruction(const QString&  target, const QString&  data);
    bool  resolveEntity(const QString&  publicId, const QString&  systemId, QXmlInputSource*&  ret);
    void setDocumentLocator(QXmlLocator*  locator);
    bool  skippedEntity(const QString&  name);
    bool  startCDATA();
    bool  startDTD(const QString&  name, const QString&  publicId, const QString&  systemId);
    bool  startDocument();
    bool  startElement(const QString&  namespaceURI, const QString&  localName, const QString&  qName, const QXmlAttributes&  atts);
    bool  startEntity(const QString&  name);
    bool  startPrefixMapping(const QString&  prefix, const QString&  uri);
    bool  unparsedEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId, const QString&  notationName);
    bool  warning(const QXmlParseException&  exception);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLDEFAULTHANDLER_H
