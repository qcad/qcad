#ifndef QTSCRIPTSHELL_QXMLSTREAMENTITYRESOLVER_H
#define QTSCRIPTSHELL_QXMLSTREAMENTITYRESOLVER_H

#include <qxmlstream.h>

#include <QtScript/qscriptvalue.h>

class QtScriptShell_QXmlStreamEntityResolver : public QXmlStreamEntityResolver
{
public:
    QtScriptShell_QXmlStreamEntityResolver();
    ~QtScriptShell_QXmlStreamEntityResolver();

    QString  resolveEntity(const QString&  publicId, const QString&  systemId);
    QString  resolveUndeclaredEntity(const QString&  name);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLSTREAMENTITYRESOLVER_H
