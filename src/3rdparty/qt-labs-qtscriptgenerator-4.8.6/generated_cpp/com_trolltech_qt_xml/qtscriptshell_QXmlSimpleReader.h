#ifndef QTSCRIPTSHELL_QXMLSIMPLEREADER_H
#define QTSCRIPTSHELL_QXMLSIMPLEREADER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlSimpleReader : public QXmlSimpleReader
{
public:
    QtScriptShell_QXmlSimpleReader();
    ~QtScriptShell_QXmlSimpleReader();

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
    bool  parse(const QXmlInputSource*  input, bool  incremental);
    bool  parseContinue();
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

#endif // QTSCRIPTSHELL_QXMLSIMPLEREADER_H
