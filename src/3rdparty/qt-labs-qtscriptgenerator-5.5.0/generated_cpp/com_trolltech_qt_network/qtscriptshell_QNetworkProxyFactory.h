#ifndef QTSCRIPTSHELL_QNETWORKPROXYFACTORY_H
#define QTSCRIPTSHELL_QNETWORKPROXYFACTORY_H

#include <qnetworkproxy.h>

#include <QtScript/qscriptvalue.h>
#include <__package_shared.h>

class QtScriptShell_QNetworkProxyFactory : public QNetworkProxyFactory
{
public:
    QtScriptShell_QNetworkProxyFactory();
    ~QtScriptShell_QNetworkProxyFactory();

    QList<QNetworkProxy >  queryProxy(const QNetworkProxyQuery&  query = QNetworkProxyQuery());

    QScriptValue __qtscript_self;
};

#endif // QTSCRIPTSHELL_QNETWORKPROXYFACTORY_H
