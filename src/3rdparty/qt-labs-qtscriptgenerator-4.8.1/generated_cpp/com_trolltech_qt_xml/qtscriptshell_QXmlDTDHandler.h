#ifndef QTSCRIPTSHELL_QXMLDTDHANDLER_H
#define QTSCRIPTSHELL_QXMLDTDHANDLER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlDTDHandler : public QXmlDTDHandler
{
public:
    QtScriptShell_QXmlDTDHandler();
    ~QtScriptShell_QXmlDTDHandler();

    QString  errorString() const;
    bool  notationDecl(const QString&  name, const QString&  publicId, const QString&  systemId);
    bool  unparsedEntityDecl(const QString&  name, const QString&  publicId, const QString&  systemId, const QString&  notationName);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLDTDHANDLER_H
