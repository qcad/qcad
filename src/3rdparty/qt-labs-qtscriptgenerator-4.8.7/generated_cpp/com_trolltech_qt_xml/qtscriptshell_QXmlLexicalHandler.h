#ifndef QTSCRIPTSHELL_QXMLLEXICALHANDLER_H
#define QTSCRIPTSHELL_QXMLLEXICALHANDLER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlLexicalHandler : public QXmlLexicalHandler
{
public:
    QtScriptShell_QXmlLexicalHandler();
    ~QtScriptShell_QXmlLexicalHandler();

    bool  comment(const QString&  ch);
    bool  endCDATA();
    bool  endDTD();
    bool  endEntity(const QString&  name);
    QString  errorString() const;
    bool  startCDATA();
    bool  startDTD(const QString&  name, const QString&  publicId, const QString&  systemId);
    bool  startEntity(const QString&  name);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLLEXICALHANDLER_H
