#ifndef QTSCRIPTSHELL_QXMLREADER_H
#define QTSCRIPTSHELL_QXMLREADER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QXmlReader : public QXmlReader
{
public:
    QtScriptShell_QXmlReader();
    ~QtScriptShell_QXmlReader();

    QXmlDTDHandler*  DTDHandler() const;
    QXmlContentHandler*  contentHandler() const;
    QXmlDeclHandler*  declHandler() const;
    QXmlEntityResolver*  entityResolver() const;
    QXmlErrorHandler*  errorHandler() const;
    bool  feature(const QString&  name, bool*  ok = 0) const;
    bool  hasFeature(const QString&  name) const;
    bool  hasProperty(const QString&  name) const;
    QXmlLexicalHandler*  lexicalHandler() const;
    bool  parse(const QXmlInputSource&  input);
    bool  parse(const QXmlInputSource*  input);
    void*  property(const QString&  name, bool*  ok = 0) const;
    void setContentHandler(QXmlContentHandler*  handler);
    void setDTDHandler(QXmlDTDHandler*  handler);
    void setDeclHandler(QXmlDeclHandler*  handler);
    void setEntityResolver(QXmlEntityResolver*  handler);
    void setErrorHandler(QXmlErrorHandler*  handler);
    void setFeature(const QString&  name, bool  value);
    void setLexicalHandler(QXmlLexicalHandler*  handler);
    void setProperty(const QString&  name, void*  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLREADER_H
