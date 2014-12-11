#ifndef QTSCRIPTSHELL_QXMLENTITYRESOLVER_H
#define QTSCRIPTSHELL_QXMLENTITYRESOLVER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QXmlEntityResolver : public QXmlEntityResolver
{
public:
    QtScriptShell_QXmlEntityResolver();
    ~QtScriptShell_QXmlEntityResolver();

    QString  errorString() const;
    bool  resolveEntity(const QString&  publicId, const QString&  systemId, QXmlInputSource*&  ret);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLENTITYRESOLVER_H
