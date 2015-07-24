#ifndef QTSCRIPTSHELL_QSSLCONFIGURATION_H
#define QTSCRIPTSHELL_QSSLCONFIGURATION_H

#include <qsslconfiguration.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QSslConfiguration : public QSslConfiguration
{
public:
    QtScriptShell_QSslConfiguration();
    QtScriptShell_QSslConfiguration(const QSslConfiguration&  other);
    ~QtScriptShell_QSslConfiguration();


    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QSSLCONFIGURATION_H
