#ifndef QTSCRIPTSHELL_QXMLERRORHANDLER_H
#define QTSCRIPTSHELL_QXMLERRORHANDLER_H

#include <qxml.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QXmlErrorHandler : public QXmlErrorHandler
{
public:
    QtScriptShell_QXmlErrorHandler();
    ~QtScriptShell_QXmlErrorHandler();

    bool  error(const QXmlParseException&  exception);
    QString  errorString() const;
    bool  fatalError(const QXmlParseException&  exception);
    bool  warning(const QXmlParseException&  exception);

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QXMLERRORHANDLER_H
