#ifndef QTSCRIPTSHELL_QXMLDECLHANDLER_H
#define QTSCRIPTSHELL_QXMLDECLHANDLER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlDeclHandler : public QXmlDeclHandler
{
public:
    QtScriptShell_QXmlDeclHandler();
    ~QtScriptShell_QXmlDeclHandler();

    bool  attributeDecl(const QString&  eName, const QString&  aName, const QString&  type, const QString&  valueDefault, const QString&  value);
    QString  errorString() const;
    bool  externalEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId);
    bool  internalEntityDecl(const QString&  name, const QString&  value);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLDECLHANDLER_H
